/* Rubin + Robert */
#include "roundstatusbar.h"
#include "roundhandler.h"
#include "player.h"
#include "foodmodal.h"
#include "resourcelocationmodal.h"
#include "resourcelocation.h"
#include "buildingcardmodal.h"
#include "buildingcardsdeck.h"
#include "variablebuildingcard.h"
#include "fixedbuildingcard.h"
#include "civilizationcardmodal.h"
#include "activecivilizationcard.h"
#include "CivilizationCards/itemdicecivilizationcard.h"
#include "CivilizationCards/resourcechoicecivilizationcard.h"
#include "CivilizationCards/additionalcivilizationcard.h"
#include "itemdicemodal.h"
#include "resourcechoicemodal.h"
#include "views/itemdicemodal.h"

#include <QHBoxLayout>
#include <QMessageBox>
#include <QStyle>

RoundStatusBar::RoundStatusBar(RoundHandler* roundHandler, QWidget *parent)
    : QFrame(parent), m_roundHandler{roundHandler}
{
    m_label = new QLabel{};
    m_cancelButton = new QPushButton{"Cancel Workers"};
    m_confirmButton = new QPushButton{"Confirm Workers"};

    // Disable the confirm and cancel buttons
    enableButtons(false);
    // Show the correct player's name
    updateLabel();
    // Add the widgets to a layout
    auto layout{new QHBoxLayout};
    layout->addWidget(m_label);
    layout->addWidget(m_confirmButton);
    layout->addWidget(m_cancelButton);

    setLayout(layout);

    m_cancelButton->setObjectName("red-button");
    m_confirmButton->setObjectName("green-button");

    connect(m_cancelButton, &QPushButton::clicked, this, &RoundStatusBar::cancelTurn);
    connect(m_confirmButton, &QPushButton::clicked, this, &RoundStatusBar::confirmTurn);
    connect(m_roundHandler, &RoundHandler::addedWorkerToLocation, [=](){this->enableButtons();});
    connect(m_roundHandler, &RoundHandler::changedCurrentPlayer, this, &RoundStatusBar::updateLabel);
    connect(m_roundHandler, &RoundHandler::useResourcesForFood, this, &RoundStatusBar::openFoodModal);
    connect(m_roundHandler, &RoundHandler::pickToolsForResource, this, &RoundStatusBar::openResourceLocationModal);
    connect(m_roundHandler, &RoundHandler::buyBuildingCard, this, &RoundStatusBar::openBuildingCardModal);
    connect(m_roundHandler, &RoundHandler::buyCivilizationCard, this, &RoundStatusBar::openCivilizationCardModal);
    connect(m_roundHandler, &RoundHandler::useActiveModal, this, &RoundStatusBar::checkActiveModals);
}


/*
 * Enable / Disable the cancel and confirm button
 * @param show: true if buttons need to be enabled, false if they need to be disabled
*/
void RoundStatusBar::enableButtons(bool show)
{
    m_cancelButton->setEnabled(show);
    m_confirmButton->setEnabled(show);
}


/*
 * Cancel the turn
*/
void RoundStatusBar::cancelTurn()
{
    m_roundHandler->cancelTurn();
    enableButtons(false);
}


/*
 * Confirm the turn
*/
void RoundStatusBar::confirmTurn()
{
    m_roundHandler->confirmTurn();
    enableButtons(false);
}


/*
 * Update the player's name
*/
void RoundStatusBar::updateLabel()
{
    int playerNumber = static_cast<int>(m_roundHandler->getCurrentPlayer()->getColor()) +1;
    QString labelText{QString("Player %1's turn: ").arg(playerNumber)};
    m_label->setText(labelText);
    m_label->setObjectName("title");
    setObjectName(QString("border%1").arg(playerNumber-1));
    style()->unpolish(this);
    style()->polish(this);
    update();

}


/*
 * Open a modal to pick resources for food
 * @param amount: Amount of resources the player needs to choose
*/
void RoundStatusBar::openFoodModal(int amount)
{
    FoodModal* foodModal = new FoodModal(amount, m_roundHandler->getCurrentPlayer(), this);
    foodModal->exec();
}


/*
 * Open a modal to pick tools for a resource location
 * @param: The resource location that is used in the modal
*/
void RoundStatusBar::openResourceLocationModal(ResourceLocation* location)
{
    ResourceLocationModal* resourceLocationModal{new ResourceLocationModal(m_roundHandler->getCurrentPlayer(), location)};
    resourceLocationModal->exec();
}


/*
 * Open a modal to buy a variable building card
 * @param buildingCardsDeck: the deck where the card is located that needs to be bought
*/
bool RoundStatusBar::openBuildingCardModal(BuildingCardsDeck* buildingCardsDeck)
{
    auto activeCard = buildingCardsDeck->getActiveCard();
    int dialogResult = QDialog::Rejected;
    // If the active card is a variable card open the buildingcardmodal
    if (auto variableBuildingCard = dynamic_cast<VariableBuildingCard*>(activeCard)) {
        auto modal{new BuildingCardModal(m_roundHandler->getCurrentPlayer(), variableBuildingCard)};
        dialogResult = modal->exec();
        if (dialogResult == QDialog::Accepted) {
            buildingCardsDeck->applyReward(m_roundHandler->getCurrentPlayer());
            return true;
        } else if (dialogResult == QDialog::Rejected)
            return false;
        else
            return true;
    } else if (auto fixedCard = dynamic_cast<FixedBuildingCard*>(activeCard)){
        if (fixedCard->buyCard(m_roundHandler->getCurrentPlayer(), m_roundHandler->getCurrentPlayer()->getResources())) {
            buildingCardsDeck->applyReward(m_roundHandler->getCurrentPlayer());
            // Show success messagebox
            QMessageBox successMessageBox{QMessageBox::Information, "Completed", "Successfully bought the buildingcard!", QMessageBox::Ok, this};
                    successMessageBox.exec();
        } else {
            // show failed messagebox
            QMessageBox failedMessageBox{QMessageBox::Information, "Failed", "Failed to buy the buildingcard!", QMessageBox::Ok, this};
            failedMessageBox.exec();
        }
    }

    return true;
}


/* Robert
 * Open a modal to buy a civilization building card
 * Apply the card reward if bought
 * @param activeCard: the card that needs to be bought
*/
bool RoundStatusBar::openCivilizationCardModal(ActiveCivilizationCard* activeCard)
{
    // Get civilization card and current player
    auto civilizationCard{activeCard->getCivilizationCard()};
    auto currentplayer{m_roundHandler->getCurrentPlayer()};

    // Open modal to buy card
    auto modal{new CivilizationCardModal(currentplayer, civilizationCard, activeCard->getResourcesNeeded())};
    int dialogResult = modal->exec();

    // Depending on the result the function will return a bool whether to remove the worker
    if (dialogResult == QDialog::Accepted) {

        // Check if the card is a ItemDiceCard and proceed to open his modal
        if (const auto itemDiceCard = dynamic_cast<ItemDiceCivilizationCard*>(civilizationCard)) {
           itemDiceCard->calculateRewards();
            auto itemDiceModal = new ItemDiceModal{itemDiceCard, currentplayer, this};
            m_activeModals.append(itemDiceModal);
            itemDiceModal->exec();
        }

        // Check if the card is a resourceChoiceCard and proceed to open his modal
        else if(const auto resourceChoiceCard = dynamic_cast<ResourceChoiceCivilizationCard*>(civilizationCard)) {
            auto resourceChoiceModal{new ResourceChoiceModal{currentplayer, this}};
            resourceChoiceModal->exec();
        }

        // Check if the card is an additional card and proceed to open a messagebox to see the additional card
        else if (const auto additionalCard = dynamic_cast<AdditionalCivilizationCard*>(civilizationCard)) {
            QMessageBox additionalCardMsgBox;
            additionalCardMsgBox.setText("You got an additional card!");
            additionalCardMsgBox.setIconPixmap(QPixmap{additionalCard->getTopCard()->getImagePath()});
            additionalCardMsgBox.setDefaultButton(QMessageBox::Ok);
            additionalCardMsgBox.exec();
        }

        // Apply the card reward
        activeCard->applyReward(currentplayer);

        return true;

    } else if (dialogResult == QDialog::Rejected) {
        return false;
    } else { // If dialogResult > 1
        return true;
    }
}


/* Robert
 * Check if there are active itemDiceModals and proceed to open them
*/
void RoundStatusBar::checkActiveModals(Player* player)
{

    for (int i = 0; i < m_activeModals.size(); ++i) {
        auto activeModal = m_activeModals[i];
        if (activeModal->setPlayer(player))
            activeModal->exec();
        if (!activeModal->rewardsLeft()) {
            delete activeModal;
            m_activeModals.remove(i);
            --i;
        }
    }



}
