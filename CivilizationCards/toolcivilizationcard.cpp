/* Robert */
#include "toolcivilizationcard.h"

#include "player.h"
#include "tool.h"

ToolCivilizationCard::ToolCivilizationCard(QJsonObject derivedCardObject)
    : CivilizationCard(derivedCardObject.value("card").toObject())
{}


/*
 * Apply card reward
*/
void ToolCivilizationCard::applyReward(Player *player)
{
    // Level-up tool if possible
    foreach(auto tool, player->getTools())
        if (tool->incrementLevel())
            break;
}


/*
 * @return QJsonObject of the class
*/
QJsonObject ToolCivilizationCard::toJSON() const
{
    QJsonObject card{CivilizationCard::toJSON()};
    QJsonObject derivedCard;
    derivedCard.insert("type", 7);
    derivedCard.insert("card", card);

    return derivedCard;
}
