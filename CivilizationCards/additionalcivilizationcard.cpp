/* Robert */
#include "additionalcivilizationcard.h"
#include "player.h"

AdditionalCivilizationCard::AdditionalCivilizationCard(QJsonObject derivedCardObject)
    : CivilizationCard(derivedCardObject.value("card").toObject()), m_topCard{nullptr}
{}


/*
 * Set m_topCard with param
 * @param card: CivilizationCard to set
*/
void AdditionalCivilizationCard::setTopCard(CivilizationCard *card)
{
    m_topCard = card;
}


/*
 * Getter for m_topCard
 * @returns m_topCard
*/
CivilizationCard* AdditionalCivilizationCard::getTopCard() const
{
    return m_topCard;
}


/*
 * Take m_topCard and set it on nullptr
 * @return taken CivilizationCard*
*/
CivilizationCard* AdditionalCivilizationCard::takeTopCard()
{
    CivilizationCard* cardPtrCopy{m_topCard};
    m_topCard = nullptr;
    return cardPtrCopy;
}


/*
 * Apply card reward
*/
void AdditionalCivilizationCard::applyReward(Player *player)
{
    if (m_topCard != nullptr)
        player->addCivilizationCard(m_topCard);
}


/*
 * @return QJsonObject of the class
*/
QJsonObject AdditionalCivilizationCard::toJSON() const
{
    QJsonObject card{CivilizationCard::toJSON()};
    QJsonObject derivedCard;
    if (m_topCard != nullptr)
        derivedCard.insert("topcard", m_topCard->toJSON());
    derivedCard.insert("type", 0);
    derivedCard.insert("card", card);
    return derivedCard;
}


AdditionalCivilizationCard::~AdditionalCivilizationCard()
{
    delete m_topCard;
}
