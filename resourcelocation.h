/* Rubin */
#ifndef RESOURCELOCATION_H
#define RESOURCELOCATION_H

#include "location.h"
#include "dice.h"

class LocationPlace;
class Resource;

class ResourceLocation : public Location
{
public:
    // Constructor
    ResourceLocation(QJsonObject resourceLocationObject);

    // Getters
    int getPlayerDiceRoll(const Player* player); // returns the total value of all the dices that have been rolled
    int getPossibleResourceAmount(const Player* player); // returns the amount of resources a player can recieve
    const Resource* getResource() const; // returns all the resources

    void applyReward(Player* player) override; // Reward the player for placing his workers on the location
    void useTool(const Player *player, Tool* tool); // Use a tool to increase the reward for a player
    void removeWorker(Player* player) override; // remove all the workers of a given player from the location
    QJsonObject toJSON() const override; // return JSON object of the class

    // Destructor
    ~ResourceLocation();
private:
    void rollDices(const Player* player); // Roll Dice for a given player
    QVector<QPair<Player::Color, QVector<int>>> m_playerDiceRolls; // Save all the dice rolls with corresponding color
    const Resource* m_resource;
    Dice m_dice;
};

#endif // RESOURCELOCATION_H
