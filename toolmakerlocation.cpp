/* Robert */
#include "toolmakerlocation.h"
#include "tool.h"
#include "tooldeck.h"
#include "player.h"

#include <QJsonArray>
#include <QVector>

ToolMakerLocation::ToolMakerLocation(QJsonObject toolMakerLocationObject) : Location{toolMakerLocationObject}
{
    QJsonArray tools = toolMakerLocationObject.value("tools").toArray();
    QVector<Tool*> toolsVector;
    for (int i = 0; i < tools.size(); ++i)
        toolsVector.append(new Tool{tools[i].toObject()});
    m_toolDeck = new ToolDeck{toolsVector};
}


/* Rubin
 * Give a new tool or increment a tool of a player
 * @param player: player who will recieve a new tool or an upgraded tool
*/
void ToolMakerLocation::applyReward(Player* player)
{
    const int maxToolAmount{3};
    auto playerTools{player->getTools()};
    // If the player has less than 3 tools give him a level 1 tool.
    if (playerTools.length() < maxToolAmount) {
        auto levelOneToolIndex = m_toolDeck->getToolIndex(1);
        // If there are no tools left leave
        if (levelOneToolIndex == -1)
            return;
        // Give the player a tool
        player->addTool(m_toolDeck->getAtIndex(levelOneToolIndex));
        // Remove the tool from the vector
        return;
    }
    // If a tool has been upgraded end the function
    for (auto& tool : playerTools)
        if (tool->incrementLevel())
            return;
    // If the tools aren't upgradable check if they're all level 4
    int upgradableTool{-1};
    const int maxLevel{4};
    for (int i = 0; i < playerTools.length() && upgradableTool == -1; ++i)
        if (playerTools[i]->getLevel() < maxLevel)
            upgradableTool = i;
    // Get a level 3 tool
    auto levelThreeToolIndex{m_toolDeck->getToolIndex(3)};
    // If there are no tools left return
    if (levelThreeToolIndex == -1)
        return;
    // Add the players tool to m_tools
    m_toolDeck->addTool(playerTools[upgradableTool]);
    playerTools[upgradableTool] = m_toolDeck->getAtIndex(levelThreeToolIndex);
    // remove the tool that the player now has

}


/*
 * Add a worker from the player on the locationplace
 * @param locationplace: the location you want to place a worker on
 * @param player: the owner of the worker
 * @returns false if a worker didn't get added, else true
*/
bool ToolMakerLocation::addWorker(LocationPlace *locationplace, Player *player)
{
    // if there are no tools left then don't allow to add a worker
    if (m_toolDeck->getTools().length() == 0)
        return false;
    return Location::addWorker(locationplace, player);
}


/*
 * Getter for m_toolDeck
 * @returns m_toolDeck
*/
ToolDeck *ToolMakerLocation::getToolDeck() const
{
    return m_toolDeck;
}


/*
 * @return QJsonObject of the class
*/
QJsonObject ToolMakerLocation::toJSON() const
{
    QJsonObject toolMakerLocationObj = Location::toJSON();
    QJsonArray tools;
    for (auto& tool: m_toolDeck->getTools())
        tools.append(tool->toJSON());
    toolMakerLocationObj.insert("type", "ToolMakerLocation");
    toolMakerLocationObj.insert("tools", tools);
    return toolMakerLocationObj;
}
