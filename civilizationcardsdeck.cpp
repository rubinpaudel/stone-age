/* Robert */
#include "civilizationcardsdeck.h"
#include "civilizationcard.h"
#include "activecivilizationcard.h"

#include "CivilizationCards/additionalcivilizationcard.h"
#include "CivilizationCards/agriculturecivilizationcard.h"
#include "CivilizationCards/itemdicecivilizationcard.h"
#include "CivilizationCards/pointscivilizationcard.h"
#include "CivilizationCards/resourcechoicecivilizationcard.h"
#include "CivilizationCards/resourcecivilizationcard.h"
#include "CivilizationCards/resourcedicecivilizationcard.h"
#include "CivilizationCards/toolcivilizationcard.h"
#include "CivilizationCards/uniquetoolcivilizationcard.h"

#include <QJsonArray>

CivilizationCardsDeck::CivilizationCardsDeck(QJsonObject deckObject)
{
    initializeActiveCards(deckObject.value("activecards").toArray());

    initializeCivCards(deckObject.value("civilizationcards").toArray());

    shuffleCards();

    // Check if there are cards on the board
    bool noCardsOnBoard{true};
    for (auto& activeCard : m_activeCards)
        if (activeCard->getCivilizationCard() != nullptr)
            noCardsOnBoard = false;

    if (noCardsOnBoard)
        refillActiveCards();
    else {
        // If an active card has an additional card, give it's m_topCard
        foreach(auto activeCard, m_activeCards) {
            if (auto additionalCard = dynamic_cast<AdditionalCivilizationCard*>(activeCard->getCivilizationCard())) {
                if (!isEmpty())
                    additionalCard->setTopCard(m_civilizationCards.takeFirst());
            }
        }
    }
}


/*
 * Initialize all active cards to m_activeCards from the QJsonArray
 * @param activeCardsArray: the QJsonArray with all active cards
*/
void CivilizationCardsDeck::initializeActiveCards(QJsonArray activeCardsArray)
{
    static const int activeCardsAmount{4};
    m_activeCards.resize(activeCardsAmount);

    for (int i = 0; i < activeCardsArray.size(); ++i) {
        QJsonObject cardData{activeCardsArray[i].toObject()};
        m_activeCards[i] = new ActiveCivilizationCard{cardData};
    }
}


/*
 * Initialize all civilization cards to m_civilizationCards from the QJsonArray
 * @param civilizationCardsArray: the QJsonArray with all civilization cards
*/
void CivilizationCardsDeck::initializeCivCards(QJsonArray civilizationCardsArray)
{

    static const int civCardsAmount{36};
    m_civilizationCards.reserve(civCardsAmount);

    for (int i = 0; i < civilizationCardsArray.size(); ++i) {
        QJsonObject cardData{civilizationCardsArray[i].toObject()};

        CivilizationCard* civCardPtr{nullptr};
        switch (cardData.value("type").toInt()) {
        case 0:
            civCardPtr = new AdditionalCivilizationCard{cardData};
            break;
        case 1:
            civCardPtr = new AgricultureCivilizationCard{cardData};
            break;
        case 2:
            civCardPtr = new ItemDiceCivilizationCard{cardData};
            break;
        case 3:
            civCardPtr = new PointsCivilizationCard{cardData};
            break;
        case 4:
            civCardPtr = new ResourceChoiceCivilizationCard{cardData};
            break;
        case 5:
            civCardPtr = new ResourceCivilizationCard{cardData};
            break;
        case 6:
            civCardPtr = new ResourceDiceCivilizationCard{cardData};
            break;
        case 7:
            civCardPtr = new ToolCivilizationCard{cardData};
            break;
        case 8:
            civCardPtr = new UniqueToolCivilizationCard{cardData};
            break;
        default:
            break;

        }

        // Set civilization cards for active cards
        if (cardData.value("isactive").toBool(false)) {
            int j{cardData.value("activecard").toInt()};
            m_activeCards[j]->setCivilizationCard(civCardPtr);
        }
        else
            m_civilizationCards.append(civCardPtr);
    }
}


/*
 * Shuffle the deck m_civilizationCards
*/
void CivilizationCardsDeck::shuffleCards()
{
    int newPos;
    for (int i = 0; i < m_civilizationCards.size(); ++i) {
        newPos = i + rand() % (m_civilizationCards.size() - i);
        m_civilizationCards.swapItemsAt(i, newPos);
    }
}


/*
 * Removes the first card of the deck
*/
void CivilizationCardsDeck::removeFirstCard()
{
    m_civilizationCards.removeFirst();
}


/*
 * Checks if m_civilizationCards is empty
 * @return true if empty, else false
*/
bool CivilizationCardsDeck::isEmpty() const
{
    return m_civilizationCards.isEmpty();
}


/*
 * Refill all active cards by first checking if the left cards can be moved to the right
*/
void CivilizationCardsDeck::refillActiveCards()
{
    // If an active card has an additional card, give it's m_topCard back to m_civilizationCards
    foreach(auto activeCard, m_activeCards) {
        if (auto additionalCard = dynamic_cast<AdditionalCivilizationCard*>(activeCard->getCivilizationCard())) {
            auto card = additionalCard->takeTopCard();
            if (card != nullptr)
                m_civilizationCards.push_front(card);
        }

    // Don't refill if the deck is empty
    }
    if (isEmpty())
        return;

    // Loop over every activeCard to refill
    int iterator;
    for (int currentIndex = m_activeCards.size() - 1; currentIndex >= 0; --currentIndex) {
        iterator = 1;
        while (m_activeCards[currentIndex]->getCivilizationCard() == nullptr) {

            // No card to move to the right was found
            if (currentIndex - iterator < 0) {
                m_activeCards[currentIndex]->setCivilizationCard(m_civilizationCards.takeFirst());
                break;
            }
            // Found a card to move to the right
            if (m_activeCards[currentIndex - iterator]->getCivilizationCard() != nullptr) {
                m_activeCards[currentIndex]->setCivilizationCard(m_activeCards[currentIndex - iterator]->takeCivilizationCard());
                break;
            }
            ++iterator;
        }
    }

    // If an active card has an additional card, give it's m_topCard back
    foreach(auto activeCard, m_activeCards) {
        if (auto additionalCard = dynamic_cast<AdditionalCivilizationCard*>(activeCard->getCivilizationCard())) {
            if (!isEmpty())
                additionalCard->setTopCard(m_civilizationCards.takeFirst());
        }
    }
}


/*
 * Getter for m_activeCards
 * @return m_activeCards
*/
QVector<ActiveCivilizationCard *> CivilizationCardsDeck::getActiveCards() const
{
  return m_activeCards;
}


/*
 * @return QJsonObject of the class
*/
QJsonObject CivilizationCardsDeck::toJSON() const
{
    // Put active cards in a QJsonArray
    QJsonArray activeCardsArray;
    foreach(auto activeCard, m_activeCards)
        activeCardsArray.append(activeCard->toJSON());

    // Put the civilization cards that are active in a QJsonArray with json data
    QJsonArray civCardsArray;
    for(int i = 0; i < m_activeCards.length(); ++i) {
        if (auto civCard = m_activeCards[i]->getCivilizationCard() != nullptr) {
            QJsonObject civCardObj{m_activeCards[i]->getCivilizationCard()->toJSON()};
            civCardObj.insert("isactive", true);
            civCardObj.insert("activecard", i);
            civCardsArray.append(civCardObj);
        }
    }

    // Append the civilization cards that are not active to that array
    foreach(auto civilizationCard, m_civilizationCards)
        civCardsArray.append(civilizationCard->toJSON());

    // Create a QJsonObject and insert the 2 QJsonArrays
    QJsonObject civilizationCardsDeckObj;
    civilizationCardsDeckObj.insert("civilizationcards", civCardsArray);
    civilizationCardsDeckObj.insert("activecards", activeCardsArray);

    return civilizationCardsDeckObj;

}


CivilizationCardsDeck::~CivilizationCardsDeck()
{
    for (auto& card : m_civilizationCards)
        delete card;
    for (auto& card: m_activeCards)
        delete card;
}
