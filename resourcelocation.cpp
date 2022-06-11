/* Rubin */
#include "resourcelocation.h"
#include "player.h"
#include "resource.h"
#include "locationplace.h"
#include "tool.h"

ResourceLocation::ResourceLocation(QJsonObject resourceLocationObject)
    : Location{resourceLocationObject},
      m_resource{new Resource{resourceLocationObject.value("resource").toObject()}}, m_dice{}
{
}


/*
 * Give the player resources with the amount they have rolled
 * @param player: player who will get the reward
*/
void ResourceLocation::applyReward(Player* player)
{
    // get the amount of resources a player will get
    int resourceAmount = getPossibleResourceAmount(player);
    player->addResource(m_resource->getType(), resourceAmount);
}


/*
 * Use a tool to increment the amount of resources a player will get
 * @param player: player of whom we are incrementing the amount
 * @param tool: tool that needs to be used
*/
void ResourceLocation::useTool(const Player* player, Tool* tool)
{
    auto playerColor = player->getColor();
    auto toolValue = tool->getLevel();
    // find the player's dicerolls and append the toolValue to the total amount
    for (int i = 0; i < m_playerDiceRolls.length(); ++i)
        if (m_playerDiceRolls[i].first == playerColor)
            m_playerDiceRolls[i].second.append(toolValue);
    tool->setUsed(true);
}


/*
 * @return resource that will be rewarded
*/
const Resource* ResourceLocation::getResource() const
{
    return m_resource;
}


/*
 * Remove all the workers of a given player from all the location places,
 * and empty the previous player rolls
 * @param player: the player of who we need to remove the workers
*/
void ResourceLocation::removeWorker(Player *player)
{
    /* remove the players from the location*/
    Location::removeWorker(player);

    /* Find the player's dice rolls and remove it */
    int playerRollsIndex = 0;
    for (int i = 0; i < m_playerDiceRolls.length(); ++i)
        if (m_playerDiceRolls[i].first == player->getColor())
            return m_playerDiceRolls.remove(playerRollsIndex);
}


/*
 * Get the sum of all the dicerolls of a player
 * @param player: player of whom we are returning the sum of the dicerolls
 * @return sum of the dicerolls
*/
int ResourceLocation::getPlayerDiceRoll(const Player *player)
{

    auto playerColor = player->getColor();
    for (int i = 0; i < m_playerDiceRolls.length(); ++i) {
        // Check if the color of the rolls match with the player color
        if (m_playerDiceRolls[i].first == playerColor)
        {
            int sum = 0;
            auto playerRolls = m_playerDiceRolls[i].second;
            // calculate the sum of all the dicerolls
            for (int j = 0; j < playerRolls.length(); ++j)
                sum += playerRolls[j];
            // return the sum
            return sum;
        }
    }

    // if the player hasn't rolled yet roll for player and call the function again
    rollDices(player);
    return getPlayerDiceRoll(player);
}


/*
 * Return the amount of resources a player will get
 * @param player: player of whom we are returning the amount of resources
 * @return amount of resources
*/
int ResourceLocation::getPossibleResourceAmount(const Player *player)
{
    return getPlayerDiceRoll(player) / m_resource->getValue();
}


/*
 * Roll a dice n amount of times, (n = amount of workers in the location of a player)
 * @param player: player that we are rolling the dice for
*/
void ResourceLocation::rollDices(const Player *player)
{
    auto playerColor = player->getColor();
    // Find the amount of workers in the current location
    int diceAmount = Location::getPlayerWorkerAmount(player);
    // roll the dice
    QVector<int> diceRolls;
    for (int i = 0; i < diceAmount; ++i)
        diceRolls.append(m_dice.rollDice());
    // add the dice rolls to the list
    m_playerDiceRolls.append(QPair<Player::Color, QVector<int>>{playerColor, diceRolls});
}


/*
 * @return QJsonObject of the class
*/
QJsonObject ResourceLocation::toJSON() const
{
    QJsonObject resourceLocationObj = Location::toJSON();
    resourceLocationObj.insert("resource", m_resource->toJSON());
    resourceLocationObj.insert("type", "ResourceLocation");
    return resourceLocationObj;
}



ResourceLocation::~ResourceLocation()
{
    delete m_resource;
}
