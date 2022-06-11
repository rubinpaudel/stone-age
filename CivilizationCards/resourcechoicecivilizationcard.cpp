/* Robert */
#include "resourcechoicecivilizationcard.h"
#include "player.h"

ResourceChoiceCivilizationCard::ResourceChoiceCivilizationCard(QJsonObject derivedCardObject)
    : CivilizationCard(derivedCardObject.value("card").toObject())
{}


/*
 * Empty function for completeness virtual function
*/
void ResourceChoiceCivilizationCard::applyReward(Player *player)
{
    return;
}


/*
 * @return QJsonObject of the class
*/
QJsonObject ResourceChoiceCivilizationCard::toJSON() const
{
    QJsonObject card{CivilizationCard::toJSON()};
    QJsonObject derivedCard;
    derivedCard.insert("type", 4);
    derivedCard.insert("card", card);

    return derivedCard;
}
