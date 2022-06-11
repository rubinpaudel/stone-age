/* Robert */
#include "civilizationcardmodal.h"
#include "resourcepicker.h"
#include "civilizationcard.h"
#include "player.h"
#include "resourcepickerwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

CivilizationCardModal::CivilizationCardModal(Player *player, CivilizationCard* civilizationCard, int resourcesNeeded, QWidget *parent)
    : QDialog{parent}, m_player{player}, m_civilizationCard{civilizationCard}, m_resourcesNeeded{resourcesNeeded}
{
    // Create buy button
    m_buyButton = new QPushButton{"Buy"};
    m_buyButton->setObjectName("green-button");
    m_buyButton->setEnabled(false);

    // Create cancel button to remove workers
    QPushButton* cancelButton{new QPushButton{"Remove Worker"}};
    cancelButton->setObjectName("red-button");

    // Create close button to buy later
    QPushButton* closeButton{new QPushButton{"Buy Later"}};
    closeButton->setObjectName("default");

    // Connect buttons
    connect(m_buyButton, &QPushButton::clicked, this, &CivilizationCardModal::buyCard);
    connect(cancelButton, &QPushButton::clicked, this, &CivilizationCardModal::setResultToTwoAndClose);
    connect(closeButton, &QPushButton::clicked, this, &CivilizationCardModal::rejectAndClose);

    // Create button layout
    QVBoxLayout* buttonLayout{new QVBoxLayout};
    buttonLayout->addWidget(m_buyButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(closeButton);

    // Create modal title
    QLabel* title = new QLabel("Buy Civilization card");
    title->setAlignment(Qt::AlignHCenter);

    // Create card pixmap
    QLabel* image = new QLabel;
    image->setPixmap(QPixmap{m_civilizationCard->getImagePath()}.scaled(150, 150, Qt::KeepAspectRatio));

    initializeResourcePickers();

    // Create horizontal layout
    QHBoxLayout* hLayout{new QHBoxLayout};
    hLayout->addWidget(image);
    hLayout->addWidget(m_resourcePickerWidget);

    // Create vertical layout
    QVBoxLayout* mainLayout{new QVBoxLayout};
    mainLayout->addWidget(title);
    mainLayout->addLayout(hLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    setAttribute(Qt::WA_DeleteOnClose);
}


/*
* Check if resources in pickers are correct, if so make the button enabled
*/
void CivilizationCardModal::checkResources()
{
    // Get all the values from the resourcePickers
    int totalAmount = 0;
    for (auto& resource : m_resourcePickerWidget->getResourcePickerValues())
        totalAmount += resource->getAmount();

    // Enable button if values are correct
    if (totalAmount == m_resourcesNeeded)
        m_buyButton->setEnabled(true);
    else
        m_buyButton->setEnabled(false);
}


/*
* Buy the card and close the modal with Accepted result
*/
void CivilizationCardModal::buyCard()
{
    // Substract resources from player
    m_civilizationCard->buyCard(m_player, m_resourcePickerWidget->getResourcePickerValues());

    done(QDialog::Accepted);
}


/*
* Set the result to Rejected and close the modal
*/
void CivilizationCardModal::rejectAndClose()
{
    done(QDialog::Rejected);
}


/*
* Set the result to '2' and close the modal
*/
void CivilizationCardModal::setResultToTwoAndClose()
{
    done(2);
}


/*
* Initialize the resource pickers made out of QSpinbox's and connect their value changed to checkResources()
*/
void CivilizationCardModal::initializeResourcePickers()
{
    // Get player resources
    int woodAmount = m_player->getResource(Resource::ResourceType::Wood)->getAmount();
    int brickAmount = m_player->getResource(Resource::ResourceType::Brick)->getAmount();
    int stoneAmount = m_player->getResource(Resource::ResourceType::Stone)->getAmount();
    int goldAmount = m_player->getResource(Resource::ResourceType::Gold)->getAmount();

    // Create resourcePickerWidget with maximum amounts
    m_resourcePickerWidget = new ResourcePickerWidget(woodAmount, brickAmount, stoneAmount, goldAmount);
    connect(m_resourcePickerWidget, &ResourcePickerWidget::resourcePickerChanged, this, &CivilizationCardModal::checkResources);
}
