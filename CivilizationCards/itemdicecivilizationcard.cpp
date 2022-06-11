/* Robert */
#include "itemdicecivilizationcard.h"
#include "player.h"
#include "tool.h"

ItemDiceCivilizationCard::ItemDiceCivilizationCard(QJsonObject derivedCardObject)
    : CivilizationCard(derivedCardObject.value("card").toObject())
{}


/* Rubin
 * Roll 4 dice and save them to the rewards array
*/
void ItemDiceCivilizationCard::calculateRewards()
{

    for (int i = 0; i < MAX_REWARDS; ++i)
        m_rewards.append(m_dice.rollDice());
}


/* Rubin
 * @return all the available rewards
*/
QVector<int> ItemDiceCivilizationCard::getRewards() const
{
    return m_rewards;
}

/* Rubin
 * @return true is there are rewards left, false if there aren't
*/
bool ItemDiceCivilizationCard::hasRewardsLeft() const
{
    return (MAX_REWARDS - m_players.length()) > 0;
}


/* rubin
 * add a player to to the players whi have recieved a reward
 * @param player : player that needs to be added to the list
*/
void ItemDiceCivilizationCard::addPlayer(const Player *player)
{
    m_players.append(player->getColor());
}


/* Rubin
 * Check if a player has already picked a resource
*/
bool ItemDiceCivilizationCard::isValidPlayer(const Player *player)
{
    for (auto& playerColor : m_players)
        if (playerColor == player->getColor())
            return false;
    return true;
}


/* Rubin
 * Give the correct reward to the given player
 * @param player : player who will get the reward
 * @param rewardType : the reward type the player will recieve
*/
void ItemDiceCivilizationCard::rewardPlayer(Player *player, int rewardType)
{
    switch (rewardType) {
    case 1:
        player->addResource(Resource::ResourceType::Wood, 1);
        break;
    case 2:
        player->addResource(Resource::ResourceType::Brick, 1);
        break;
    case 3:
        player->addResource(Resource::ResourceType::Stone, 1);
        break;
    case 4:
        player->addResource(Resource::ResourceType::Gold, 1);
        break;
    case 5:
        foreach(auto tool, player->getTools())
            if (tool->incrementLevel())
                break;
        break;
    case 6:
        player->addAgricultureLevel(1);
        break;
    }
    addPlayer(player);

}


/*
 * Empty function for completeness virtual function
*/
void ItemDiceCivilizationCard::applyReward(Player *player)
{
    return;
}


/*
 * @return QJsonObject of the class
*/
QJsonObject ItemDiceCivilizationCard::toJSON() const
{
    QJsonObject card{CivilizationCard::toJSON()};
    QJsonObject derivedCard;
    derivedCard.insert("type", 2);
    derivedCard.insert("card", card);

    return derivedCard;
}
