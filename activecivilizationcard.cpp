/* Robert */
#include "activecivilizationcard.h"
#include "civilizationcard.h"

ActiveCivilizationCard::ActiveCivilizationCard(QJsonObject cardObject)
    : Location(cardObject),
      m_resourcesNeeded{cardObject.value("resourceneeded").toInt()},
      m_civilizationCard{nullptr}
{}


/*
 * Applies the card reward and gives the card to the player that bought it
*/
void ActiveCivilizationCard::applyReward(Player *player)
{
    m_civilizationCard->applyReward(player);
    player->addCivilizationCard(m_civilizationCard);
    m_civilizationCard = nullptr;
    emit changedActiveCard();
}


/*
 * Getter for m_resourcesNeeded
 * @return: m_resourcesNeeded
*/
int ActiveCivilizationCard::getResourcesNeeded() const
{
    return m_resourcesNeeded;
}


/*
 * Getter for m_civilizationCard
 * @return: m_civilizationCard
*/
CivilizationCard *ActiveCivilizationCard::getCivilizationCard() const
{
    return m_civilizationCard;
}


/*
 * Take m_civilizationCard for return and set it as nullptr after
 * @return: m_civilizationCard
*/
CivilizationCard *ActiveCivilizationCard::takeCivilizationCard()
{
    auto civCardPtrCopy{m_civilizationCard};
    m_civilizationCard = nullptr;
    emit changedActiveCard();
    return civCardPtrCopy;
}


/*
 * Setter for m_civilizationCard
 * @param civizationCard: the civilizationCard you want to set it to
*/
void ActiveCivilizationCard::setCivilizationCard(CivilizationCard *civilizationCard)
{
    m_civilizationCard = civilizationCard;
    emit changedActiveCard();
}


/*
 * Setter for  m_resourcesNeeded
 * @param value: the value you want to set it to
*/
void ActiveCivilizationCard::setResourcesNeeded(int value)
{
    m_resourcesNeeded = value;
}


/*
 * @return QJsonObject of the class
*/
QJsonObject ActiveCivilizationCard::toJSON() const
{
    QJsonObject activeCardObject{Location::toJSON()};
    activeCardObject.insert("resourceneeded", m_resourcesNeeded);
    return activeCardObject;
}


ActiveCivilizationCard::~ActiveCivilizationCard()
{
    delete m_civilizationCard;
}

