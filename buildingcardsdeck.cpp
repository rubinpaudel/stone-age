/* Rubin */
#include "buildingcardsdeck.h"

#include "buildingcard.h"
#include "fixedbuildingcard.h"
#include "variablebuildingcard.h"

#include <QJsonArray>

BuildingCardsDeck::BuildingCardsDeck(QJsonObject deckObject)
    : Location{deckObject}
{
    m_activeCardIndex = deckObject.value("activecardindex").toInt();
    QJsonArray buildingCards{deckObject.value("buildingcards").toArray()};
    /* Place all the cards in a vector */
    for (int i = 0; i < buildingCards.size(); ++i) {
        QJsonObject card = buildingCards[i].toObject();
        if (card.value("type").toInt() == 0)
            m_buildingCards.append(new FixedBuildingCard(card));
        else
            m_buildingCards.append(new VariableBuildingCard(card));
    }

}


/*
 * Change the activeCard in the deck
*/
void BuildingCardsDeck::next()
{
    if (m_buildingCards.length() > 0) {
        ++m_activeCardIndex;
        m_activeCardIndex %= m_buildingCards.length();  // if the index is out of bound find the correct index
    } else
        m_activeCardIndex = -1;
    emit changedActiveCard();
}


/*
 * @return active card of the deck, if there are no cards it returns a nullptr
*/
BuildingCard* BuildingCardsDeck::getActiveCard() const
{
    if (m_buildingCards.length() == 0)
        return nullptr;
    return m_buildingCards[m_activeCardIndex];
}


/*
 * @return returns if the deck is empty or not
*/
bool BuildingCardsDeck::isEmpty() const
{
    return m_buildingCards.isEmpty();
}

/*
 * Add a building card to the deck
 * @param card : the card that needs to be added in the stack
*/
void BuildingCardsDeck::addCard(BuildingCard *card)
{
    m_buildingCards.append(card);
}


/*
 * @return the amount of cards in the deck
*/
int BuildingCardsDeck::getRemainingCards() const
{
    return m_buildingCards.size();
}


/*
 * Give the player the active building card
 * @param player: the player who will recieve the card
*/
void BuildingCardsDeck::applyReward(Player* player)
{
    player->addBuildingCard(m_buildingCards[m_activeCardIndex]);
    m_buildingCards.remove(m_activeCardIndex);
    next();
}


/*
 * @return JSON object of the deck
*/
QJsonObject BuildingCardsDeck::toJSON() const
{
    QJsonObject buildingCardsDeckobj = Location::toJSON();
    // Add activecardindec to the obj
    buildingCardsDeckobj.insert("activecardindex", m_activeCardIndex);
    // Create buildingCards Object
    QJsonArray cards;
    // If the card is a Fixed type add it to the fixed array, else add it to the variable array
    for (auto& card : m_buildingCards)
        cards.append(card->toJSON());
    buildingCardsDeckobj.insert("buildingcards", cards);
    return buildingCardsDeckobj;
}


BuildingCardsDeck::~BuildingCardsDeck()
{
    for (auto& card : m_buildingCards)
        delete card;
}
