/* Robert */
#include "itemdicemodal.h"
#include "player.h"
#include <QLabel>
#include <QGridLayout>
#include "player.h"
#include "resource.h"
#include "tool.h"
#include "CivilizationCards/itemdicecivilizationcard.h"


ItemDiceModal::ItemDiceModal(ItemDiceCivilizationCard* card,  Player* player, QWidget* parent)
    : QDialog{parent}, m_player{player}, m_itemDiceCard{card}
{
    // Create title
    QLabel* title{new QLabel("Choose your reward")};
    title->setAlignment(Qt::AlignHCenter);

    // Create a grid layout for the reward buttons
    QGridLayout* rewardLayout{new QGridLayout};
    static const int colums{3};

    static const int playerAmount{4}; // Hardcoded amount of players
    m_rewardTypeButtons.reserve(playerAmount);

    // Create reward button for every player
    int row{0}, column{0};

    for (auto& diceRolled : m_itemDiceCard->getRewards()) {

        // Create image path for correct reward
        QString imagePath;
        if (diceRolled <= 4)
            imagePath = ":/assets/resources/gameassets/resource" + QString::number(diceRolled) + ".png";
        else if (diceRolled == 5)
            imagePath = ":/assets/resources/gameassets/toolLevel1.jpg";
        else
            imagePath = ":/assets/resources/gameassets/agriculture.png";

        // Create reward button
        const int size{75};
        QPushButton* rewardButton{new QPushButton};
        rewardButton->setFlat(true);
        rewardButton->setMaximumSize(size, size);
        rewardButton->setAutoDefault(false);
        rewardButton->setIcon(QIcon{QPixmap{imagePath}});
        rewardButton->setIconSize(QSize{size, size});

        rewardButton->setProperty("rewardType", diceRolled);
        m_rewardTypeButtons.append(rewardButton); // Append a QPair with button and diceRolled


        connect(rewardButton, &QPushButton::clicked, this, &ItemDiceModal::giveReward);

        // Add to grid layout
        rewardLayout->addWidget(rewardButton, row, column);

        // Make grid layout pretty
        ++column;
        if (column == colums - 1) {
            column = 0;
            ++row;
        }
    }

    // Create and set main layout
    QVBoxLayout* mainlayout{new QVBoxLayout};
    mainlayout->addWidget(title);
    mainlayout->addLayout(rewardLayout);
    setModal(true);
    setLayout(mainlayout);
}


/* Rubin
 * Set m_player to give the reward to
 * @param: player to give the reward to
*/
bool ItemDiceModal::setPlayer(Player* player)
{
    if (m_itemDiceCard->isValidPlayer(player)) {
        m_player = player;
        return true;
    }
    return false;
}


/* Rubin
 * @return true if there are rewards left false if there aren't any left
*/
bool ItemDiceModal::rewardsLeft() const
{
    return m_itemDiceCard->hasRewardsLeft();
}



/* Rubin
 * Give the reward the player picked
*/
void ItemDiceModal::giveReward()
{
    // get the button that sent the signal
    auto button = qobject_cast<QPushButton *>(sender());
    int rewardType = button->property("rewardType").toInt();

    m_itemDiceCard->rewardPlayer(m_player, rewardType);
    // Remove reward button
    removeButton(rewardType);

}

/* Rubin
 * Remove the buttons that have already been used
*/
void ItemDiceModal::removeButton(int rewardType)
{
    // Remove reward button
    for (int i = 0; i < m_rewardTypeButtons.size(); ++i) {
        if (m_rewardTypeButtons[i]->property("rewardType").toInt() == rewardType) {
            delete m_rewardTypeButtons[i];
            m_rewardTypeButtons.remove(i);
            break;
        }
    }
    if (m_rewardTypeButtons.isEmpty())
        close();
    else
        hide();
}
