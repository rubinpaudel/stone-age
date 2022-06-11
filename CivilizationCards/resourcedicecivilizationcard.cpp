/* Robert */
#include "resourcedicecivilizationcard.h"
#include "player.h"

ResourceDiceCivilizationCard::ResourceDiceCivilizationCard(QJsonObject derivedCardObject)
    : CivilizationCard(derivedCardObject.value("card").toObject()), m_dice{},
      m_type{static_cast<Resource::ResourceType>(derivedCardObject.value("resourcetype").toInt())},
      m_value{derivedCardObject.value("resourcevalue").toInt()}
{}


/*
 * Apply card reward
*/
void ResourceDiceCivilizationCard::applyReward(Player *player)
{
    static const int diceRolls{2}; // Always roll 2 dices
    int diceSum{0}, resourceAmount;
    for (int i = 0; i < diceRolls; ++i)
        diceSum += m_dice.rollDice();
    resourceAmount = diceSum / m_value;
    player->addResource(m_type, resourceAmount);
}


/*
 * @return QJsonObject of the class
*/
QJsonObject ResourceDiceCivilizationCard::toJSON() const
{
    QJsonObject card{CivilizationCard::toJSON()};
    QJsonObject derivedCard;
    derivedCard.insert("resourcevalue", m_value);
    derivedCard.insert("resourcetype", static_cast<int>(m_type));
    derivedCard.insert("type", 6);
    derivedCard.insert("card", card);

    return derivedCard;
}
