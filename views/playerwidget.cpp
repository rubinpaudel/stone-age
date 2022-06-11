/* Robert */
#include "playerwidget.h"
#include "player.h"
#include "playeritem.h"
#include "view_config.h"
#include "buildingcardsviewer.h"
#include "civilizationcardsviewer.h"

#include <QGridLayout>

PlayerWidget::PlayerWidget(Player* player, QWidget* parent)
    : QFrame(parent), m_player{player}
{
    // Create main layout
    QVBoxLayout* mainLayout{new QVBoxLayout};
    mainLayout->addLayout(maketitle());
    mainLayout->addLayout(makeGridLayout());
    setLayout(mainLayout);

    // Create card viewers
    m_buildingCardsViewer = new BuildingCardsViewer{m_player->getBuildingCards()};
    m_civilizationCardsViewer = new CivilizationCardsViewer{m_player->getCivilizationCards()};

    // Connect updates and buttons
    connect(m_player, &Player::updatedCivilizationCards, this, &PlayerWidget::updateCards);
    connect(m_player, &Player::updatedScore, this, &PlayerWidget::updateScore);
    connect(m_player, &Player::updatedResources, this, &PlayerWidget::updateResources);
    connect(m_player, &Player::updatedBuildings, this, &PlayerWidget::updateBuildings);
    connect(m_player, &Player::updatedLevel, this, &PlayerWidget::updateLevel);
    connect(m_player, &Player::updatedWorkers, this, &PlayerWidget::updateWorker);
    connect(m_buildingsButton, &QPushButton::clicked, this, &PlayerWidget::openBuildingCardsViewer);
    connect(m_civilizationButton, &QPushButton::clicked, this, &PlayerWidget::openCivilizationCardsViewer);
}

/*
 * Creates the title for the player widget with score and name
 * @return: the title in QHBoxLayout* form
*/
QHBoxLayout* PlayerWidget::maketitle()
{
    // Create score label and layout
    QHBoxLayout* scoreLayout{new QHBoxLayout};
    m_scoreLabel = new QLabel(QString::number(m_player->getScore()));
    scoreLayout->addWidget(m_scoreLabel);

    // Create score icon and add to layout
    QLabel* scoreIcon{new QLabel};
    QPixmap starPixmap(":/assets/resources/gameassets/star.png");
    static const int pixSize{15};
    scoreIcon->setPixmap(starPixmap.scaled(pixSize, pixSize));
    scoreLayout->addWidget(scoreIcon);
    scoreLayout->addStretch();

    // Create main layout and add player name
    QHBoxLayout* titleLayout{new QHBoxLayout};
    auto playerNumber = static_cast<int>(m_player->getColor());
    QString playerName{QString("Player %1:").arg(playerNumber + 1)};
    auto playerNameLabel{new QLabel(playerName)};
    playerNameLabel->setObjectName("title-player");
    titleLayout->addWidget(playerNameLabel);
    titleLayout->addLayout(scoreLayout);
    setObjectName(QString("border%1").arg(playerNumber));

    return titleLayout;
}


/*
 * Creates the grid layout for all items
 * @return: the layout in QGridLayout* form
*/
QGridLayout* PlayerWidget::makeGridLayout()
{
    // Create buttons
    m_buildingsButton = new QPushButton(tr("&Buildings"));
    m_civilizationButton = new QPushButton(tr("&Civilization Cards"));
    m_buildingsButton->setObjectName("default");
    m_civilizationButton->setObjectName("default");

    QGridLayout* layout{new QGridLayout};

    static const int amountResources{5};
    m_resourcePlayerItems.reserve(amountResources);

    PlayerItem* item{nullptr};

    // Create all player items in put them in grid layout
    auto resourceItem = m_player->getResource(Resource::ResourceType::Food);
    item = new PlayerItem{resourceItem->getImgPath(), "Food", QString::number(resourceItem->getAmount()), this};
    m_resourcePlayerItems.append(item);
    layout->addWidget(item, 0, 0);

    resourceItem = m_player->getResource(Resource::ResourceType::Wood);
    item = new PlayerItem{resourceItem->getImgPath(), "Wood", QString::number(resourceItem->getAmount()), this};
    m_resourcePlayerItems.append(item);
    layout->addWidget(item, 1, 0);

    resourceItem = m_player->getResource(Resource::ResourceType::Brick);
    item = new PlayerItem{resourceItem->getImgPath(), "Brick", QString::number(resourceItem->getAmount()), this};
    m_resourcePlayerItems.append(item);
    layout->addWidget(item, 2, 0);

    resourceItem = m_player->getResource(Resource::ResourceType::Stone);
    item = new PlayerItem{resourceItem->getImgPath(), "Stone", QString::number(resourceItem->getAmount()), this};
    m_resourcePlayerItems.append(item);
    layout->addWidget(item, 1, 1);

    resourceItem = m_player->getResource(Resource::ResourceType::Gold);
    item = new PlayerItem{resourceItem->getImgPath(), "Gold", QString::number(resourceItem->getAmount()), this};
    m_resourcePlayerItems.append(item);
    layout->addWidget(item, 2, 1);

    item = new PlayerItem{":/assets/resources/gameassets/agriculture.png", "Agriculture Level", QString::number(m_player->getAgricultureLevel()), this};
    m_levelPlayerItem = item;
    layout->addWidget(item, 0, 2);

    QString workerPixMapPath{QString(":/assets/resources/gameassets/worker%1.png").arg(static_cast<int>(m_player->getColor()))};
    QString workerValue{QString::number(m_player->getAvailableWorkerAmount()) + "/" + QString::number(m_player->getTotalWorkerAmount())};
    item = new PlayerItem{workerPixMapPath, "Workers", workerValue, this};
    m_workerPlayerItem = item;
    layout->addWidget(item, 0, 1);

    layout->addWidget(m_buildingsButton, 1, 2);
    layout->addWidget(m_civilizationButton, 2, 2);

    return layout;
}


/*
 * Update the new score
*/
void PlayerWidget::updateScore()
{
    m_scoreLabel->setText(QString::number(m_player->getScore()));
}


/*
 * Update the new resources
*/
void PlayerWidget::updateResources()
{
    m_resourcePlayerItems[0]->changeValue(QString::number(m_player->getResource(Resource::ResourceType::Food)->getAmount()));
    m_resourcePlayerItems[1]->changeValue(QString::number(m_player->getResource(Resource::ResourceType::Wood)->getAmount()));
    m_resourcePlayerItems[2]->changeValue(QString::number(m_player->getResource(Resource::ResourceType::Brick)->getAmount()));
    m_resourcePlayerItems[3]->changeValue(QString::number(m_player->getResource(Resource::ResourceType::Stone)->getAmount()));
    m_resourcePlayerItems[4]->changeValue(QString::number(m_player->getResource(Resource::ResourceType::Gold)->getAmount()));

}


/*
 * Update the new worker amount
*/
void PlayerWidget::updateWorker()
{
    QString workerValue{QString::number(m_player->getAvailableWorkerAmount()) + "/" + QString::number(m_player->getTotalWorkerAmount())};
    m_workerPlayerItem->changeValue(workerValue);
}


/*
 * Update the new agriculture level
*/
void PlayerWidget::updateLevel()
{
    m_levelPlayerItem->changeValue(QString::number(m_player->getAgricultureLevel()));
}


/*
 * Update the new buildings
*/
void PlayerWidget::updateBuildings()
{
    m_buildingCardsViewer->setCards(m_player->getBuildingCards());
}


/*
 * Update the new civilization cards
*/
void PlayerWidget::updateCards()
{
    m_civilizationCardsViewer->setCards(m_player->getCivilizationCards());
}


/*
 * Open the building cards viewer
*/
void PlayerWidget::openBuildingCardsViewer()
{
    m_buildingCardsViewer->exec();
}


/*
 * Open the civilization cards viewer
*/
void PlayerWidget::openCivilizationCardsViewer()
{
    m_civilizationCardsViewer->exec();
}
