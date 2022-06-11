/* Robert */
#include "agriculturecivilizationcard.h"
#include "player.h"

AgricultureCivilizationCard::AgricultureCivilizationCard(QJsonObject derivedCardObject) \
    : CivilizationCard(derivedCardObject.value("card").toObject())
{}


/*
 * Apply card reward
*/
void AgricultureCivilizationCard::applyReward(Player *player)
{
    player->addAgricultureLevel(1);
}


/*
 * @return QJsonObject of the class
*/
QJsonObject AgricultureCivilizationCard::toJSON() const
{
    QJsonObject card{CivilizationCard::toJSON()};
    QJsonObject derivedCard;
    derivedCard.insert("type", 1);
    derivedCard.insert("card", card);

    return derivedCard;
}
