/* Robert */
#include "resourcecivilizationcard.h"

#include "player.h"

ResourceCivilizationCard::ResourceCivilizationCard(QJsonObject derivedCardObject)
    : CivilizationCard(derivedCardObject.value("card").toObject()),
      m_amount{derivedCardObject.value("resourceamount").toInt()},
      m_type{static_cast<Resource::ResourceType>(derivedCardObject.value("resourcetype").toInt())}
{}


/*
 * Apply card reward
*/
void ResourceCivilizationCard::applyReward(Player *player)
{
    player->addResource(m_type, m_amount);
}


/*
 * @return QJsonObject of the class
*/
QJsonObject ResourceCivilizationCard::toJSON() const
{
    QJsonObject card{CivilizationCard::toJSON()};
    QJsonObject derivedCard;
    derivedCard.insert("resourcetype", static_cast<int>(m_type));
    derivedCard.insert("resourceamount", m_amount);
    derivedCard.insert("type", 5);
    derivedCard.insert("card", card);

    return derivedCard;
}
