/* Rubin */
#include "foodmodal.h"
#include "resourcepicker.h"
#include "resourcepickerwidget.h"

#include <QPushButton>
#include <QVBoxLayout>

FoodModal::FoodModal(int amountNeeded, Player* player, QWidget* parent)
    : QDialog{parent}, m_pickedAmount{0}, m_amountNeeded{amountNeeded}, m_player{player}
{

    // Create cancel and confirm buttons
    m_cancelButton = new QPushButton{"Cancel"};
    m_confirmButton = new QPushButton{"Confirm"};
    m_confirmButton->setEnabled(false);

    m_cancelButton->setObjectName("red-button");
    m_confirmButton->setObjectName("green-button");

    int playerNumber = static_cast<int>(m_player->getColor()) + 1;

    // Create the title and center it
    QLabel* title{new QLabel{QString("Out of food! Pick resources player %1").arg(playerNumber)}};
    title->setAlignment(Qt::AlignHCenter);
    // Create the amount label and center it
    m_amountLabel = new QLabel{};
    m_amountLabel->setAlignment(Qt::AlignHCenter);
    setAmountLabel();
    // create the resourcepickers
    initializeResourcePickers();
    // Create the button and main layout
    QHBoxLayout* buttonlayout{new QHBoxLayout{}};
    buttonlayout->addWidget(m_cancelButton);
    buttonlayout->addWidget(m_confirmButton);
    QVBoxLayout* mainLayout{new QVBoxLayout{}};
    mainLayout->addWidget(title);
    mainLayout->addWidget(m_amountLabel);
    mainLayout->addWidget(m_resourcePickerWidget);
    mainLayout->addLayout(buttonlayout);
    setLayout(mainLayout);
    // Remove the close button
    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);

    connect(m_cancelButton, &QPushButton::clicked, this, &FoodModal::cancel);
    connect(m_confirmButton, &QPushButton::clicked, this, &FoodModal::confirm);
}


/*
 * Use the resources chosen by the player instead of food
*/
void FoodModal::confirm()
{
    /* Remove Resources from player */

    for (auto& resource : m_resourcePickerWidget->getResourcePickerValues())
        m_player->addResource(resource->getType(), -resource->getAmount());
    accept();
    close();
}


/*
 *
*/
void FoodModal::cancel()
{
    /* Remove 10 Points from the player */
    const int scorePenalty{-10};
    m_player->addScore(scorePenalty);
    accept();
}


/*
 * Update the amount label with the remaining amount
*/
void FoodModal::setAmountLabel()
{
    // Format the string with the remaining amount and change the text of the label
    QString amountLabelText{QString("Amount needed: %1").arg(m_amountNeeded - m_pickedAmount)};
    m_amountLabel->setText(amountLabelText);
}


/*
 * When a resource is picked, check if the player needs to select more to continue
*/
void FoodModal::pickedResource()
{
    m_pickedAmount = 0;
    for (auto& resource : m_resourcePickerWidget->getResourcePickerValues())
        m_pickedAmount += resource->getAmount();

    if (m_pickedAmount == m_amountNeeded)
        m_confirmButton->setEnabled(true);
    else
        m_confirmButton->setEnabled(false);

    setAmountLabel();
}


/*
 * Create the resource pickers
*/
void FoodModal::initializeResourcePickers()
{
    int woodAmount = m_player->getResource(Resource::ResourceType::Wood)->getAmount();
    int brickAmount = m_player->getResource(Resource::ResourceType::Brick)->getAmount();
    int stoneAmount = m_player->getResource(Resource::ResourceType::Stone)->getAmount();
    int goldAmount = m_player->getResource(Resource::ResourceType::Gold)->getAmount();
    m_resourcePickerWidget = new ResourcePickerWidget(woodAmount, brickAmount, stoneAmount, goldAmount);
    connect(m_resourcePickerWidget, &ResourcePickerWidget::resourcePickerChanged, this, &FoodModal::pickedResource);

}
