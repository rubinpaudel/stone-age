/* Robert */
#include "uniquetoolcivilizationcard.h"
#include "player.h"
#include "tool.h"

UniqueToolCivilizationCard::UniqueToolCivilizationCard(QJsonObject derivedCardObject)
    : CivilizationCard(derivedCardObject.value("card").toObject()),
      m_tool{new Tool{derivedCardObject.value("tool").toObject()}}
{}


/*
 * Apply card reward
*/
void UniqueToolCivilizationCard::applyReward(Player *player)
{
    player->addTool(m_tool);
}


/*
 * @return QJsonObject of the class
*/
QJsonObject UniqueToolCivilizationCard::toJSON() const
{
    QJsonObject card{CivilizationCard::toJSON()};
    QJsonObject derivedCard;
    derivedCard.insert("tool", m_tool->toJSON());
    derivedCard.insert("type", 5);
    derivedCard.insert("card", card);

    return derivedCard;
}


UniqueToolCivilizationCard::~UniqueToolCivilizationCard()
{
    delete m_tool;
}
