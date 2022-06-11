/* Rubin */
#ifndef ROUNDHANDLER_H
#define ROUNDHANDLER_H
#include <QObject>
#include <QVector>

class Player;
class ResourceLocation;
class Location;
class LocationPlace;
class BuildingCardsDeck;
class ActiveCivilizationCard;
class Board;

class RoundHandler : public QObject
{
    Q_OBJECT
public:
    enum class GamePhase {Placing, Collecting, Feeding};

    // Constructor
    RoundHandler(QJsonObject roundHandlerObject);

    // Getters
    QVector<Player*> getPlayers() const; // return all the players
    Player* getCurrentPlayer() const; // return the current player
    Player* getStartPlayer() const; // return the startplayer
    Board* getBoard() const;
    Player* getWinner() const; // return the player with the highest score

    void cancelTurn(); // Cancel the current turn
    void confirmTurn(); // Confirm the current turn
    void makeMove(LocationPlace* locationPlace = nullptr);
    QJsonObject toJSON() const; // return a JSON Object of the roundhandler

    // Destructor
    ~RoundHandler();
signals:
    void addedWorkerToLocation();
    void changedCurrentPlayer();
    void removedWorkersFromLocation(Location* location);
    void useResourcesForFood(int amount);
    void pickToolsForResource(ResourceLocation* location);
    bool buyBuildingCard(BuildingCardsDeck* deck);
    bool buyCivilizationCard(ActiveCivilizationCard* civCard);
    void useActiveModal(Player* player);
    void gameEnded(Player* player);
private:

    void feedPlayerWorkers(); // feed the workers of all players
    void placePlayerWorkers(Location *location, LocationPlace *locationPlace); // place a worker on a location
    void collectPlayerWorkers(Location *location, LocationPlace *locationPlace); // remove a worker from a location
    void endGame(); // Check if the game is done
    void changePhase(); // Change the gamePhase
    void changeTurn(); // Change the current turn
    void initializeNewRound(); // Initialize a new round

    QVector<Player*> m_players;
    int m_currentPlayerIndex;
    int m_startPlayerIndex;
    GamePhase m_gamePhase;
    Location* m_selectedLocation;
    QVector<LocationPlace*> m_currentMovePlaces;
    Board* m_board;
};

#endif // ROUNDHANDLER_H
