/* Rubin */
#include "resourcelocationmodal.h"
#include "player.h"
#include "tool.h"
#include "resourcelocation.h"
#include "toolbutton.h"

#include <QHBoxLayout>
#include <QPushButton>

ResourceLocationModal::ResourceLocationModal(Player* player, ResourceLocation* resourceLocation, QWidget* parent)
    : QDialog{parent}, m_player{player}, m_resourceLocation{resourceLocation}
{

    auto mainLayout{new QVBoxLayout};
    auto title{new QLabel{m_resourceLocation->getName()}};
    title->setObjectName("title");

    auto toolButtonLayout = createToolButtons();

    m_confirmButton = new QPushButton{"Confirm"};
    m_confirmButton->setObjectName("green-button");

    m_resetButton = new QPushButton{"Reset Tools"};
    m_resetButton->setObjectName("red-button");

    QHBoxLayout* buttonLayout{new QHBoxLayout};

    buttonLayout->addWidget(m_confirmButton);
    buttonLayout->addWidget(m_resetButton);

    mainLayout->addWidget(title);
    mainLayout->addLayout(createInfoLayout());
    mainLayout->addLayout(toolButtonLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    // Remove close button
    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);
    connect(m_confirmButton, &QPushButton::clicked, this, &ResourceLocationModal::confirmButtonPressed);
    connect(m_resetButton, &QPushButton::clicked, this, &ResourceLocationModal::resetButtonPressed);
    connect(m_resetButton, &QPushButton::clicked, this, &ResourceLocationModal::updateInfoMessage);
    setAttribute(Qt::WA_DeleteOnClose);
}


/*
 * Update the info label
*/
QHBoxLayout* ResourceLocationModal::createInfoLayout()
{
    m_infoLabel = new QLabel{};
    updateInfoMessage();
    // Add the resource image
    auto imageLabel{new QLabel};
    imageLabel->setPixmap(QPixmap{m_resourceLocation->getResource()->getImgPath()});
    imageLabel->setAlignment(Qt::AlignBottom);
    // Create a horizontal layout with the text and pixmap
    auto layout{new QHBoxLayout};
    layout->addWidget(m_infoLabel);
    layout->addWidget(imageLabel);
    return layout;
}


/*
 * Create a Toolbutton for each tool of the player that is not yet used
 * @return layout with toolbuttons
*/
QHBoxLayout* ResourceLocationModal::createToolButtons()
{
    auto toolButtonsLayout{new QHBoxLayout{}};
    auto title{new QLabel{"Available Tools: "}};
    toolButtonsLayout->addWidget(title);

    for (auto& tool : m_player->getTools()) {
        // If the tool is used don't add it to the list
        if (tool->getUsed())
            continue;
        // Create the button and add it to the layout
        auto button{new ToolButton{tool->getLevel(), ""}};
        m_toolButtons.append(button);
        toolButtonsLayout->addWidget(button);
        connect(button, &ToolButton::clicked, this, &ResourceLocationModal::updateInfoMessage);
    }
    toolButtonsLayout->setAlignment(Qt::AlignLeft);
    return toolButtonsLayout;
}


/*
 * Apply the tools that have been used by the player and close the modal
*/
void ResourceLocationModal::confirmButtonPressed()
{
    /* Use the selected tools */
    for (int i = 0; i < m_toolButtons.length(); ++i)
        if (m_toolButtons[i]->getSelected())
            m_resourceLocation->useTool(m_player, m_player->getTools()[i]);
    // Give the reward to the player
    m_resourceLocation->applyReward(m_player);
    // Close the modal
    accept();
    close();
}


/*
 * Make all the selected tools unselected
*/
void ResourceLocationModal::resetButtonPressed()
{
    for (auto toolButton : m_toolButtons)
        toolButton->reset();
}

void ResourceLocationModal::updateInfoMessage()
{
    // Get the data from the player
    int playerRolledAmount = m_resourceLocation->getPlayerDiceRoll(m_player);
    int diceAmount = m_resourceLocation->getPlayerWorkerAmount(m_player);
    int cost = m_resourceLocation->getResource()->getValue();
    int toolAmount{0};
    for (auto& tool : m_toolButtons)
        if (tool->getSelected())
            toolAmount += tool->property("toolvalue").toInt();
    auto infoMessage = QString("You Rolled %1 with %2 dice\nTools used : %3\nYou get (%1 + %3) / %4 = %5")
            .arg(playerRolledAmount).arg(diceAmount).arg(toolAmount).arg(cost).arg((toolAmount + playerRolledAmount) / cost);
    m_infoLabel->setText(infoMessage);
    m_infoLabel->update();
}
