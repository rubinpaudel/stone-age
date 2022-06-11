/* Rubin */
#include "buildingcardmodal.h"
#include "resourcepicker.h"
#include "variablebuildingcard.h"
#include "player.h"
#include "resourcepickerwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

BuildingCardModal::BuildingCardModal(Player *player, VariableBuildingCard *buildingCard, QWidget *parent)
    : QDialog{parent}, m_player{player}, m_buildingCard{buildingCard}
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
    connect(m_buyButton, &QPushButton::clicked, this, &BuildingCardModal::buyCard);
    connect(cancelButton, &QPushButton::clicked, this, &BuildingCardModal::setResultToTwoAndClose);
    connect(closeButton, &QPushButton::clicked, this, &BuildingCardModal::rejectAndClose);

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
    image->setPixmap(QPixmap{m_buildingCard->getImagePath()}.scaled(150, 150, Qt::KeepAspectRatio));

    initializeResourcePickers();

    auto hlayout{new QHBoxLayout};
    hlayout->addWidget(image);
    hlayout->addWidget(m_resourcePickerWidget);

    auto mainLayout{new QVBoxLayout};

    mainLayout->addWidget(title);
    mainLayout->addLayout(hlayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setAttribute(Qt::WA_DeleteOnClose);
}


/*
 * Buy the card and close the Modal
*/
void BuildingCardModal::buyCard()
{
    bool bought = m_buildingCard->buyCard(m_player, m_resourcePickerWidget->getResourcePickerValues());
    done(bought);
}


/*
 * Close the Modal
*/
void BuildingCardModal::rejectAndClose()
{
    done(QDialog::Rejected);
}


void BuildingCardModal::setResultToTwoAndClose()
{
    done(2);
}


/*
 * Check if the player can buy the card
*/
bool BuildingCardModal::checkResources()
{
    // Get all the values from the resourcePickers
    bool valid = m_buildingCard->isValidPurchase(m_resourcePickerWidget->getResourcePickerValues());
    m_buyButton->setEnabled(valid);
    return valid;
}


/*
 * Create a ResourcePickerWidget with the resources of the player
*/
void BuildingCardModal::initializeResourcePickers()
{
    // Create a layout with resourcepickers
    int woodAmount = m_player->getResource(Resource::ResourceType::Wood)->getAmount();
    int brickAmount = m_player->getResource(Resource::ResourceType::Brick)->getAmount();
    int stoneAmount = m_player->getResource(Resource::ResourceType::Stone)->getAmount();
    int goldAmount = m_player->getResource(Resource::ResourceType::Gold)->getAmount();
    m_resourcePickerWidget = new ResourcePickerWidget(woodAmount, brickAmount, stoneAmount, goldAmount);
    connect(m_resourcePickerWidget, &ResourcePickerWidget::resourcePickerChanged, this, &BuildingCardModal::checkResources);

}
