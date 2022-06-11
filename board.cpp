/* Robert */
#include "board.h"
#include "location.h"
#include "resourcelocation.h"
#include "hutlocation.h"
#include "fieldlocation.h"
#include "toolmakerlocation.h"
#include "buildingcard.h"
#include "fixedbuildingcard.h"
#include "variablebuildingcard.h"
#include "buildingcardsdeck.h"
#include "civilizationcardsdeck.h"
#include "activecivilizationcard.h"
#include <QJsonArray>
#include <algorithm>

Board::Board(QJsonObject boardObject)
{
    // Get all locations from baordObject and put them in m_locations
    QJsonArray locations  = boardObject.value("locations").toArray();
    for (int i = 0; i < locations.size(); ++i)
    {
        QJsonObject locationObject = locations[i].toObject();
        QString type = locationObject.value("type").toString();

        if (type == "ResourceLocation")
            m_locations.append(new ResourceLocation{locationObject});
        else if (type == "FieldLocation")
            m_locations.append(new FieldLocation{locationObject});
        else if (type == "HutLocation")
            m_locations.append(new HutLocation{locationObject});
        else if (type == "ToolMakerLocation")
            m_locations.append(new ToolMakerLocation{locationObject});
    }

    // Get all building cards from boardObject and put them in m_buildingCards
    QJsonObject buildingCardsDeck = boardObject.value("buildingcardsdeck").toObject();
    QJsonArray decks = buildingCardsDeck.value("decks").toArray();
    for (int i = 0; i < decks.size(); ++i)
        m_buildingCards.append(new BuildingCardsDeck{decks[i].toObject()});
    createBuildingCardsDeck(buildingCardsDeck.value("buildingcards").toArray());

    // Get all civilization cards from boardObject and put them in m_civilizationCards
    m_civilizationCards = new CivilizationCardsDeck{boardObject.value("civilizationcardsdeck").toObject()};

}


/*
 * Gets the buildingCardsObjects out of the QJsonArray and puts them in the correct decks
 * @param buildingCardsObject: the QJsonArray of buildingCardsObjects
*/
void Board::createBuildingCardsDeck(QJsonArray buildingCardsObject)
{
    QVector<BuildingCard*> buildingCards;
    if (buildingCardsObject.size() == 0)
        return;
    // Place all the cards in a vector
    for (int i = 0; i < buildingCardsObject.size(); ++i) {
        auto cardObj{buildingCardsObject[i].toObject()};
        if (cardObj.value("type").toInt() == 0)
            buildingCards.append(new FixedBuildingCard(cardObj));
        else
            buildingCards.append(new VariableBuildingCard(cardObj));
    }
    // Shuffle the building cards
    for (int i = 0; i < buildingCards.size() - 1; ++i) {
        int newPos = i + rand() % (buildingCards.size() - i);
        buildingCards.swapItemsAt(i, newPos);
    }

    // Put the cards in the right deck
    for (int i = 0; i < buildingCards.size(); ++i) {
        int rightDeck = buildingCards.size() / (m_buildingCards.size());
        rightDeck = i / rightDeck;
        m_buildingCards[rightDeck]->addCard(buildingCards[i]);
    }


}


/*
 * @param locationName: the name of the location you're looking for
 * @return the location with the given name
*/
Location* Board::getLocation(QString locationName) const
{
    for (auto location : m_locations)
        if (location->getName() == locationName)
            return location;
    for (auto buildingCard : m_buildingCards)
        if (buildingCard->getName() == locationName)
            return buildingCard;
    auto activeCards{m_civilizationCards->getActiveCards()};
    for (auto activeCard : activeCards)
        if (activeCard->getName() == locationName)
            return activeCard;
    return nullptr; // return nullptr if there is no location with the given name
}


/*
 * @return the locations
*/
QVector<Location*> Board::getLocations() const
{
    return m_locations;
}


/*
 * @return QJsonObject of the class
*/
QJsonObject Board::toJSON() const
{
    QJsonObject boardObj, buildingCardDeck;
    QJsonArray locations, buildingDeck;

    // Add Locations to json
    for (auto& location : m_locations)
        locations.append(location->toJSON());
    boardObj.insert("locations", locations);
    // Add buildingcarddecks to json
    for (auto& buildingCardDeck : m_buildingCards)
        buildingDeck.append(buildingCardDeck->toJSON());

    buildingCardDeck.insert("decks", buildingDeck);
    boardObj.insert("buildingcardsdeck", buildingCardDeck);
    boardObj.insert("civilizationcardsdeck", m_civilizationCards->toJSON());

    return boardObj;
}


/*
 * @return the building cards decks
*/
QVector<BuildingCardsDeck*> Board::getBuildingCardsDecks() const
{
    return m_buildingCards;
}


/*
 * @return the civilization cards deck
*/
CivilizationCardsDeck *Board::getCivilizationDeck() const
{
    return m_civilizationCards;
}


Board::~Board()
{
    for (auto& location : m_locations)
        delete location;

    for (auto& buildingCard : m_buildingCards)
        delete buildingCard;

    delete m_civilizationCards;
}
