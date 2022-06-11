/* Robert */
#include "resourcechoicemodal.h"
#include "resourcepicker.h"
#include "player.h"
#include "resourcepickerwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

ResourceChoiceModal::ResourceChoiceModal(Player* player, QWidget *parent)
    : QDialog{parent}, m_player{player}
{
    // Create button
    m_acceptButton = new QPushButton{"Accept"};
    m_acceptButton->setObjectName("green-button");
    m_acceptButton->setEnabled(false);
    connect(m_acceptButton, &QPushButton::clicked, this, &ResourceChoiceModal::acceptButtonClicked);

    // Create title
    QLabel* title = new QLabel("Collect 2 resources by choice");
    title->setAlignment(Qt::AlignHCenter);

    initializeResourcePickers();

    // Create and set main layout
    QVBoxLayout* mainLayout{new QVBoxLayout};
    mainLayout->addWidget(title);
    mainLayout->addWidget(m_resourcePickerWidget);
    mainLayout->addWidget(m_acceptButton);
    setLayout(mainLayout);
    setAttribute(Qt::WA_DeleteOnClose);
}


/*
 * Check if resources on picker widget are correct, if so make the button enabled
*/
void ResourceChoiceModal::checkResources()
{
    // Get all the values from the resourcePickers
    int totalAmount = 0;
    for (auto& resource : m_resourcePickerWidget->getResourcePickerValues())
        totalAmount += resource->getAmount();

    // If resources are correct set button enabled
    if (totalAmount == m_resourceAmount)
        m_acceptButton->setEnabled(true);
    else
        m_acceptButton->setEnabled(false);
}


/*
 * Create the ResourcePickerWidget and connect the value changed with checkResources()
*/
void ResourceChoiceModal::initializeResourcePickers()
{
    int woodAmount = m_player->getResource(Resource::ResourceType::Wood)->getAmount();
    int brickAmount = m_player->getResource(Resource::ResourceType::Brick)->getAmount();
    int stoneAmount = m_player->getResource(Resource::ResourceType::Stone)->getAmount();
    int goldAmount = m_player->getResource(Resource::ResourceType::Gold)->getAmount();
    m_resourcePickerWidget = new ResourcePickerWidget(woodAmount, brickAmount, stoneAmount, goldAmount);
    connect(m_resourcePickerWidget, &ResourcePickerWidget::resourcePickerChanged, this, &ResourceChoiceModal::checkResources);

}


/*
 * Give resources to player and close modal
*/
void ResourceChoiceModal::acceptButtonClicked()
{
    for (auto& resource : m_resourcePickerWidget->getResourcePickerValues())
        m_player->addResource(resource->getType(), resource->getAmount());
    close();
}
