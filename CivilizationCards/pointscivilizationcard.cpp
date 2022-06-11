/* Robert */
#include "pointscivilizationcard.h"
#include "player.h"

PointsCivilizationCard::PointsCivilizationCard(QJsonObject derivedCardObject)
    : CivilizationCard(derivedCardObject.value("card").toObject())
{}


/*
 * Apply card reward
*/
void PointsCivilizationCard::applyReward(Player *player)
{
    static const int score{3}; // Score added for every card is 3
    player->addScore(score);
}


/*
 * @return QJsonObject of the class
*/
QJsonObject PointsCivilizationCard::toJSON() const
{
    QJsonObject card{CivilizationCard::toJSON()};
    QJsonObject derivedCard;
    derivedCard.insert("type", 3);
    derivedCard.insert("card", card);

    return derivedCard;
}
