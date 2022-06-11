/* Robert */
#ifndef ITEMDICEMODAL_H
#define ITEMDICEMODAL_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include <QString>
#include <QSignalMapper>

#include "dice.h"

class ItemDiceCivilizationCard;
class Player;

class ItemDiceModal : public QDialog
{
    Q_OBJECT
public:
    ItemDiceModal(ItemDiceCivilizationCard* card, Player* player,  QWidget* parent); // Constructor
    bool setPlayer(Player* player); // Set m_player
    bool rewardsLeft() const; // check if there are still rewards left
public slots:
    void giveReward();
private:
    void removeButton(int rewardType);

    Player* m_player; // Player to give reward to
    ItemDiceCivilizationCard* m_itemDiceCard;
    QVector<QPushButton*> m_rewardTypeButtons; // Buttons in pair with the diceRolled
};

#endif // ITEMDICEMODAL_H
