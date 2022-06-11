/* Rubin */
#include "player.h"
#include "tool.h"
#include "buildingcard.h"
#include "buildingcardsdeck.h"
#include "resource.h"
#include "fixedbuildingcard.h"
#include "variablebuildingcard.h"
#include "civilizationcard.h"

#include <QJsonArray>

Player::Player(QJsonObject playerJSONObject)
{
    m_totalWorkerAmount = playerJSONObject.value("totalworkeramount").toInt();
    m_availableWorkerAmount = playerJSONObject.value("availableworkeramount").toInt();
    m_agricultureLevel = playerJSONObject.value("agriculturelevel").toInt();
    m_color = static_cast<Color>(playerJSONObject.value("color").toInt());
    m_score = playerJSONObject.value("score").toInt();
    // Create new resources and add it to the players resources vector
    QJsonArray resources = playerJSONObject.value("resources").toArray();
    for (int i = 0; i < resources.size(); ++i)
        m_resources.append(new Resource{resources[i].toObject()});
    // Create new tools and add it to the players tools vector
    QJsonArray tools = playerJSONObject.value("tools").toArray();
    for (int i = 0; i < tools.size(); ++i)
        m_tools.append(new Tool{tools[i].toObject()});
    // Create new buildingCards and add it to the players vector
    QJsonArray buildingCards = playerJSONObject.value("buildingcards").toArray();
    for (int i = 0; i < buildingCards.size(); ++i)
        if (buildingCards[i].toObject().value("type").toInt() == 0)
            m_buildingCards.append(new FixedBuildingCard{buildingCards[i].toObject()});
        else
            m_buildingCards.append(new VariableBuildingCard{buildingCards[i].toObject()});

}


/*
 * increment the total worker amount
 * @param amount: amount of new workers
*/
void Player::addWorker(int amount)
{
    m_totalWorkerAmount += amount;
    m_availableWorkerAmount += amount;
    emit updatedWorkers();
}


/*
 * increment agriculture level
 * @param amount: amount of levels
*/
void Player::addAgricultureLevel(int amount)
{
    m_agricultureLevel += amount;
    emit updatedLevel();
}


/*
 * Increase the amount of resources a player has of a resourcetype
 * @param resourceType: type of resource
 * @param amount: amount of resources
*/
void Player::addResource(Resource::ResourceType resourceType, int amount)
{
    // Find the correct resource type and increment it by amount
    for (int i = 0; i < m_resources.length(); ++i)
        if (m_resources[i]->getType() == resourceType)
            m_resources[i]->increaseAmount(amount);
    emit updatedResources();
}


/*
 * Add a building card to the list of building cards a player has
 * @param card: card that needs to be added to the list
*/
void Player::addBuildingCard(BuildingCard* card)
{
    m_buildingCards.append(card);
    addScore(card->getPoints());
    emit updatedBuildings();
}


/*
 * Add a civilization card to the list of civilization cards a player has
 * @param card: card that needs to be added to the list
*/
void Player::addCivilizationCard(CivilizationCard *card)
{
    m_civilizationCards.append(card);
    emit updatedCivilizationCards();
}


/*
 * Increment the player's score by the given amount
 * @param amount : amount of score that needs to be added
*/
void Player::addScore(int amount)
{
    m_score += amount;
    emit updatedScore();
}


/*
 * Give the player a new tool
*/
void Player::addTool(Tool *tool)
{
    m_tools.append(tool);
}


/*
 * @return the player's building cards
*/
QVector<BuildingCard*> Player::getBuildingCards() const
{
    return m_buildingCards;
}

QVector<CivilizationCard*> Player::getCivilizationCards() const
{
    return m_civilizationCards;
}


/*
 * Decrement the available workers by amount
 * @param amount: amount of workers that need to be moved
*/
void Player::moveWorkers(int amount)
{
    m_availableWorkerAmount -= amount;
    emit updatedWorkers();
}


/*
 * Return the player's resource of type resourceType
 * @param resourceType : the type of resource we need to return
 * @return player's resource of the given resourceType
*/
Resource* Player::getResource(Resource::ResourceType resourceType) const
{
    for (int i = 0; i < m_resources.length(); ++i)
        if (m_resources[i]->getType() == resourceType)
            return m_resources[i];
    return nullptr;
}

/*
 * @return all the resources a player has
*/
QVector<Resource *> Player::getResources() const
{
    return m_resources;
}


/*
 * @return the players score
*/
int Player::getScore() const
{
    return m_score;    
}


/* Rubin + Robert
 * Calculate the total score of a player : resources, civilization cards, building cards ...
 * @return total score of the player
*/
int Player::getTotalScore() const
{
    int totalScore = m_score;
    // Add each resource the player has to the total score
    for (auto& resource : m_resources)
        // If the resource type is food don't add it to the score
        if (resource->getType() != Resource::ResourceType::Food)
            totalScore += resource->getAmount();

    // Add the score of the civilization cards to the players points
    totalScore += calculateCivilizationCardsScores();

    return totalScore;
}


/*
 * @return the total workers a player has
*/
int Player::getTotalWorkerAmount() const
{
    return m_totalWorkerAmount;
}


/*
 * @return the amount of available workers
*/
int Player::getAvailableWorkerAmount() const
{
    return m_availableWorkerAmount;
}


/*
 * @return the player's agriculture level
*/
int Player::getAgricultureLevel() const
{
    return m_agricultureLevel;
}


/*
 * @return the player's tools
*/
QVector<Tool*> Player::getTools()
{
    return m_tools;
}


/*
 * @return the player's team color
*/
Player::Color Player::getColor() const
{
    return m_color;
}


/*
 * @return QJsonObject of the class
*/
QJsonObject Player::toJSON() const
{
    // create an array of resource Objects
    QJsonArray resourcesArray, toolsArray, buildingCards;
    QJsonArray civilizationCards;

    for (auto& resource : m_resources)
        resourcesArray.append(resource->toJSON());
    for (auto& tool : m_tools)
        toolsArray.append(tool->toJSON());

    for (auto& buildingCard : m_buildingCards)
        buildingCards.append(buildingCard->toJSON());

    for (auto& civilizationCard : m_civilizationCards)
        civilizationCards.append(civilizationCard->toJSON());


    QJsonObject playerJSONObject{
        {"totalworkeramount", m_totalWorkerAmount},
        {"availableworkeramount", m_availableWorkerAmount},
        {"agricultureLevel", m_agricultureLevel},
        {"resources", resourcesArray},
        {"buildingcards", buildingCards},
        {"civilizationCards", civilizationCards},
        {"color", static_cast<int>(m_color)},
        {"score", m_score},
        {"tools", toolsArray}
    };
    return playerJSONObject;
}


Player::~Player()
{
    // Resources
    for (auto& resource: m_resources) {
        delete resource;
        resource = nullptr;
    }
    // Tools
    for (auto& tool : m_tools)
        delete tool;
    // Building Cards
    for (auto& bCard : m_buildingCards)
        delete bCard;
}


/* Robert
 * Calculate the score gained from all civilization cards owned by the player
 * @return the total score calculated
*/
int Player::calculateCivilizationCardsScores() const
{
    // Put all culture card types in a set and calculate amount of normal card amounts
    int totalScore{0}, farmers{0}, toolMakers{0}, hutBuilders{0}, shaman{0};
    QVector<CivilizationCard::CardType> CultureCardSet;
    for (auto& card : m_civilizationCards) {
        int normalCardAmount = card->getNormalCardAmount();
        if (normalCardAmount == -1) // Is a culture card
            CultureCardSet.append(card->getType());
        else { // Is a normal card
            if (card->getType() == CivilizationCard::CardType::Farmer)
                farmers += normalCardAmount;
            else if (card->getType() == CivilizationCard::CardType::Toolmaker)
                toolMakers += normalCardAmount;
            else if (card->getType() == CivilizationCard::CardType::Hutbuilder)
                hutBuilders += normalCardAmount;
            else if (card->getType() == CivilizationCard::CardType::Shaman)
                shaman += normalCardAmount;
        }
    }

    // Calculate amount of non-isOneUse tools owned by the player
    int tools = 0;
    for (auto& tool : m_tools)
        if (!tool->getIsOneUse())
            ++tools;

    // Calculate normal card scores
    totalScore += toolMakers * tools;
    totalScore += farmers * m_agricultureLevel;
    totalScore += hutBuilders * m_buildingCards.size();
    totalScore += shaman * getTotalWorkerAmount();

    // Calculate amount of culture cards and duplicates
    int firstSetAmount{0};
    int secondSetAmount{0};
    while (CultureCardSet.size() > 0) {
        int amountFound = CultureCardSet.removeAll(CultureCardSet.first());
        if (amountFound == 1)
            ++firstSetAmount;
        else if (amountFound == 2) {
            ++firstSetAmount;
            ++secondSetAmount;
        }
    }
    // Calculate culture card scores
    totalScore += firstSetAmount * firstSetAmount;
    totalScore += secondSetAmount * secondSetAmount;

    return totalScore;
}
