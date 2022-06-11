/* Robert */
#ifndef ITEMDICECIVILIZATIONCARD_H
#define ITEMDICECIVILIZATIONCARD_H

#include <civilizationcard.h>
#include "dice.h"
#include "player.h"

class ItemDiceCivilizationCard : public CivilizationCard
{
public:
    ItemDiceCivilizationCard(QJsonObject derivedCardObject); // Constructor

    void calculateRewards();
    QVector<int> getRewards() const;
    bool hasRewardsLeft() const;
    void addPlayer(const Player* player);
    bool isValidPlayer(const Player* player);

    void rewardPlayer(Player* player, int rewardType);

    void applyReward(Player* player) override; // Apply card reward

    QJsonObject toJSON() const override; // Return a JSON object of the class
private:
    static const int MAX_REWARDS{4};
    Dice m_dice;
    QVector<Player::Color> m_players;
    QVector<int> m_rewards;
};

#endif // ITEMDICECIVILIZATIONCARD_H
