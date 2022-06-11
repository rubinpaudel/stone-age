/* Rubin */
#include "roundhandler.h"
#include "player.h"
#include "location.h"
#include "locationplace.h"
#include "tool.h"
#include "resourcelocation.h"
#include "buildingcardsdeck.h"
#include "civilizationcard.h"
#include "activecivilizationcard.h"
#include "board.h"
#include "civilizationcardsdeck.h"
#include <QDebug>
#include <QJsonArray>

RoundHandler::RoundHandler(QJsonObject object)
{

    m_currentPlayerIndex = object.value("currentplayer").toInt();
    m_startPlayerIndex = object.value("startplayer").toInt();
    m_gamePhase = static_cast<GamePhase>(object.value("gamephase").toInt());
    QJsonArray players = object.value("players").toArray();
    for (int i = 0; i < players.size(); ++i)
        m_players.append(new Player{players[i].toObject()});
    m_selectedLocation = nullptr;
    m_board = new Board{object.value("board").toObject()};
}


/*
 * Check the current gamephase and make the move
 * @param location: The location where the player wants to make a move
 * @param locationPlace: the place the player picked within a location
*/
void RoundHandler::makeMove(LocationPlace *locationPlace)
{
    Location* location = m_board->getLocation(locationPlace->getLocationName());
    if (m_gamePhase == GamePhase::Placing) {
        placePlayerWorkers(location, locationPlace);
    }
    else if (m_gamePhase == GamePhase::Collecting) {
        collectPlayerWorkers(location, locationPlace);
    }
}

/*
 * Check each players points, tools, agricultureLevel and amount of workers to get the winner
 * @return the player with the highest score
*/
Player *RoundHandler::getWinner() const
{
    // Set the winner equal to the first player
    Player* winner{m_players[0]};
    // Loop from index 1 so we don't compare the same player
    for (int i = 1; i < m_players.length(); ++i) {
        // if the player has a higher score set that player as the winner
        if (m_players[i]->getTotalScore() > winner->getTotalScore()) {
            winner = m_players[i];
        } else if (m_players[i]->getTotalScore() == winner->getTotalScore()) {
            // If the players have an equal amount of score compare the sum of tools, agricultureLevel and workers
            int totalScoreWinner{winner->getAgricultureLevel() + winner->getTotalWorkerAmount()},
            totalScoreOtherPlayer{m_players[i]->getAgricultureLevel() + m_players[i]->getTotalWorkerAmount()};
            // Add the value of the tools to the total score
            for (auto& tool : winner->getTools())
                totalScoreWinner += tool->getLevel();
            for (auto& tool : m_players[i]->getTools())
                totalScoreOtherPlayer += tool->getLevel();
            // if the total score of the ith player is larger then that player is the winner
            if (totalScoreOtherPlayer > totalScoreWinner)
                winner = m_players[i];
            // Check for tie.
        }
    }
    return winner;
}

/*
 * Remove all the workers of a player from the selected location
*/
void RoundHandler::cancelTurn() {
    // Remove all the workers from the selected location
    for (auto& place : m_currentMovePlaces) {
        place->removeWorker();
        getCurrentPlayer()->moveWorkers(-1);
    }
    // Set the selected location to a nullptr so the player can choose again
    m_selectedLocation = nullptr;
    // Clear the current location places
    m_currentMovePlaces.erase(m_currentMovePlaces.begin(), m_currentMovePlaces.end());
    emit removedWorkersFromLocation(m_selectedLocation);
}


/*
 * Place all the workers on the location and change the turn
*/
void RoundHandler::confirmTurn()
{
    GamePhase currentGamePhase = m_gamePhase;
    if (m_gamePhase == GamePhase::Placing) {
        // Check if the player placed the required amount of workers
        if (m_currentMovePlaces.length() < m_selectedLocation->getMinWorkerAmount())
            return;
        m_selectedLocation = nullptr;
        m_currentMovePlaces.erase(m_currentMovePlaces.cbegin(), m_currentMovePlaces.cend());
    }
    changePhase();
    if (m_gamePhase == currentGamePhase)
        changeTurn();

}


/*
 * Change the phase if the previous phase is done
*/
void RoundHandler::changePhase()
{
    // Check for each phase if the phase is done, if so change the phase
    switch (m_gamePhase) {
    case GamePhase::Placing:
        // if there are players who still have workers don't change the phase
        for (auto player : m_players)
            if (player->getAvailableWorkerAmount() != 0)
                return;
        m_gamePhase = GamePhase::Collecting;
        break;
    case GamePhase::Collecting:
        // if there are players who still have workers don't change the phase
        for (auto player : m_players)
            if (player->getAvailableWorkerAmount() != player->getTotalWorkerAmount())
                return;
        // Change the phase to feeding and set the currentplayer equal to the startplayer
        m_gamePhase = GamePhase::Feeding;
        m_currentPlayerIndex = m_startPlayerIndex;
        feedPlayerWorkers();
        break;
    case GamePhase::Feeding:
        initializeNewRound();
        break;
    }
    m_currentPlayerIndex = m_startPlayerIndex;
    emit changedCurrentPlayer();
}


/*
 * Change the current player
*/
void RoundHandler::changeTurn()
{
    // Check for each phase if we can change the turn
    if (m_gamePhase == GamePhase::Placing) {
        // change the player, if the index is out of bound make it correct
        int nextPlayerIndex = (m_currentPlayerIndex + 1) % m_players.length();
        // If the next player still has workers than return that player else go to the next player
        while (m_players[nextPlayerIndex]->getAvailableWorkerAmount() == 0)
            nextPlayerIndex = (nextPlayerIndex + 1) % m_players.length();
        m_currentPlayerIndex = nextPlayerIndex;
        emit changedCurrentPlayer();
    } else if (m_gamePhase == GamePhase::Collecting) {
        // Set the next player equal to the current player
        int nextPlayerIndex = m_currentPlayerIndex;
        // If the player still has players on the board then don't change the player
        while (m_players[nextPlayerIndex]->getAvailableWorkerAmount() == m_players[nextPlayerIndex]->getTotalWorkerAmount())
            nextPlayerIndex = (nextPlayerIndex + 1) % m_players.length();
        m_currentPlayerIndex = nextPlayerIndex;
        emit changedCurrentPlayer();
        emit useActiveModal(getCurrentPlayer());
        changePhase();
    }
    m_selectedLocation = nullptr;


}


/*
 * Feed the workers of all the players
*/
void RoundHandler::feedPlayerWorkers()
{
    // Find the last player that needs to feed their workers
    int lastPlayer;
    (m_startPlayerIndex == 0) ? lastPlayer = m_players.length() - 1 : lastPlayer = m_startPlayerIndex - 1;

    while (true) {
        auto currentPlayer = getCurrentPlayer();
        // Get the amount of food needed for a player accounting their agriculture level
        int foodNeeded = currentPlayer->getTotalWorkerAmount() - currentPlayer->getAgricultureLevel();
        // Get the player's food resource
        Resource* playerFood = currentPlayer->getResource(Resource::ResourceType::Food);
        // If the player has enough food subtract it with the needed amount
        if (foodNeeded <= playerFood->getAmount()) {
            currentPlayer->addResource(Resource::ResourceType::Food, -foodNeeded);
        } else {
            // Make the player choose to use Resources instead of food
            int amountNeeded = (foodNeeded - currentPlayer->getResource(Resource::ResourceType::Food)->getAmount());
            emit useResourcesForFood(amountNeeded);
            // Set the player's food amount to 0
            currentPlayer->addResource(Resource::ResourceType::Food, -currentPlayer->getResource(Resource::ResourceType::Food)->getAmount());
        }
        emit useActiveModal(getCurrentPlayer());
        // If the last player has given their workers food then stop the loop
        if (m_currentPlayerIndex == lastPlayer)
            break;
        // Find the next player that needs to feed their workers
        m_currentPlayerIndex = (m_currentPlayerIndex + 1) % m_players.length();
        emit changedCurrentPlayer();
        // Use the remaining active cards


    }
    changePhase();
}


/*
 * Start a new round by changing the start player and resetting the players tools
*/
void RoundHandler::initializeNewRound()
{
    m_gamePhase = GamePhase::Placing;
    // find the new start player
    m_startPlayerIndex = (m_startPlayerIndex + 1) % m_players.length();
    m_currentPlayerIndex = m_startPlayerIndex;
    // Make tools unused of all players
    for (auto& player : m_players)
        for (auto& tool : player->getTools())
            if (!tool->getIsOneUse())
                tool->setUsed(false);
    m_board->getCivilizationDeck()->refillActiveCards();

    endGame();
}


/*
 * Place a player's worker in a locationplace of the give location
 * @param location: Location where the player wants to place a worker
 * @param locationplace: the exact place in the location the player wants to place a worker
*/
void RoundHandler::placePlayerWorkers(Location *location, LocationPlace *locationPlace)
{
    // if the player previously picked a location and the location they picked now doesn't match then don't place a worker
    if (m_selectedLocation != nullptr && m_selectedLocation->getName() != location->getName())
        return;
    if (m_selectedLocation == nullptr) {
        // Check if the player has put a worker on this location during another turn
        // if the location is the Hunt location then allow them to place workers again
        if (location->getName() != "Hunt") {
            int availablePlaces{0};
            for (auto& place : location->getLocationPlaces()){
                if (place->hasWorker() && place->getWorkerColor() == getCurrentPlayer()->getColor())
                    return;
                if (!place->hasWorker())
                    ++availablePlaces;
            }
            if (availablePlaces == 0)
                return;
        }
        // Set the selected location to the picked location
        m_selectedLocation = location;

    }
    if (location->addWorker(locationPlace, getCurrentPlayer())) {
        // Add the locationPlace to the places the player slected
        m_currentMovePlaces.append(locationPlace);
        emit addedWorkerToLocation();
        m_selectedLocation = location;
    } else if (m_currentMovePlaces.length() ==0) m_selectedLocation = nullptr;
}


/*
 * Remove the workers from a location and give the player the locations reward
 * @param location: The location from which we need to remove the player
 * @param locationPlace: The exact location place the player selected
*/
void RoundHandler::collectPlayerWorkers(Location *location, LocationPlace *locationPlace)
{
    bool allowRemove{true};
    // If the location place has a worker but not from the current player then do nothing Or the place doesn't have a worker then do nothing
    if (!locationPlace->hasWorker() || (locationPlace->hasWorker() && getCurrentPlayer()->getColor() != locationPlace->getWorkerColor()))
        return;
    // If the location is a resourceLocation notify to pick tools to increment the total resources a player gets
    if (auto resourceLocation = dynamic_cast<ResourceLocation*>(location))
        emit pickToolsForResource(resourceLocation);
    // If the location is a building card notify to buy the card
    else if (auto buildingCardsDeck = dynamic_cast<BuildingCardsDeck*>(location))
        allowRemove = emit buyBuildingCard(buildingCardsDeck);
    else if (auto activeCard = dynamic_cast<ActiveCivilizationCard*>(location))
        allowRemove = emit buyCivilizationCard(activeCard);
    // If it is another type of location then just apply the reward
    else
        location->applyReward(getCurrentPlayer());
    // Remove the workers and confirm the turn
    if (allowRemove)
        location->removeWorker(getCurrentPlayer());
    confirmTurn();
}


/*
 * Check if the game is over, if the game is over it ends the game
*/
void RoundHandler::endGame()
{
    auto civilizationCardsDeck{m_board->getCivilizationDeck()};
    auto buildingCardsDecks{m_board->getBuildingCardsDecks()};

    bool gameEnd = false;
    // Check if there are civilizationcards in the activecards
    for (auto& activeCard : civilizationCardsDeck->getActiveCards())
        if (activeCard->getCivilizationCard() == nullptr)
            gameEnd = true;
    // Check if there are buildingcards left
    for (auto& buildingCardsDeck : buildingCardsDecks)
        if (buildingCardsDeck->isEmpty())
            gameEnd = true;
    if (gameEnd)
        emit gameEnded(getWinner());
}

/*
 * @return all the players
*/
QVector<Player*> RoundHandler::getPlayers() const
{
    return m_players;
}


/*
 * @return the current player
*/
Player* RoundHandler::getCurrentPlayer() const
{
    return m_players[m_currentPlayerIndex];
}


/*
 * @return the start player
*/
Player* RoundHandler::getStartPlayer() const
{
    return m_players[m_startPlayerIndex];
}


/*
 * @return the board
*/
Board *RoundHandler::getBoard() const
{
    return m_board;
}


/*
 * @return the class in JSON format
*/
QJsonObject RoundHandler::toJSON() const
{
    QJsonObject roundHandlerObject{
        {"currentplayer", m_currentPlayerIndex},
        {"gamephase", static_cast<int>(m_gamePhase)},
        {"startplayer", m_startPlayerIndex},
        {"board", m_board->toJSON()}
    };
    // Create an array of player JSON Objects
    QJsonArray players;
    for (int i = 0; i < m_players.length(); ++i)
        players.append(m_players[i]->toJSON());
    roundHandlerObject.insert("players", players);
    return roundHandlerObject;
}


RoundHandler::~RoundHandler()
{
    for (auto& player : m_players)
        delete player;
    if (m_board != nullptr)
        delete m_board;
}
