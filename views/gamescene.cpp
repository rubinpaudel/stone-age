/* Rubin */
#include "gamescene.h"
#include "resourcelocation.h"
#include "resource.h"
#include "locationrectitem.h"
#include "roundhandler.h"
#include "game.h"
#include "board.h"
#include "buildingcardsdeckview.h"
#include "variablebuildingcard.h"
#include "toolmakerlocation.h"
#include "buildingcardsdeck.h"
#include "toolrectitem.h"
#include "civilizationcardsdeck.h"
#include "activecardview.h"
#include "activecivilizationcard.h"
#include "civilizationcard.h"

GameScene::GameScene(Game* game, QObject* parent)
    : QGraphicsScene{parent}, m_game{game}, m_selectedLocation{nullptr}, m_locationRectItems{}, m_buildingCardsDeckViews{}, m_activeCardViews{}
{
    initializeScene();
}


/*
 * Check if player selected a location
*/
void GameScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    auto items = selectedItems();
    // If there is no graphics item selected stop the function
    if (items.size() <= 0)
        return QGraphicsScene::mouseReleaseEvent(mouseEvent);
    // Get the selected item and cast it to a locationrectItem
    auto selectedItem = dynamic_cast<LocationRectItem*>(items.first());
    // if the selected item is a locationrectitem set it as the selected location
    if (selectedItem) {
        m_selectedLocation = selectedItem;
        m_game->getRoundHandler()->makeMove(m_selectedLocation->getLocationPlace());
    }
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}



/*
 * Create the scene with locations, buildingcards and civiliezationcards
*/
void GameScene::initializeScene()
{
    const qreal WIDTH{1280}, HEIGHT{720};
    setSceneRect(0,0, WIDTH, HEIGHT);
    // Set the background image
    const QString backgroundImagePath{":/assets/resources/gameassets/board.jpg"};
    QPixmap backgroundPixmap{backgroundImagePath};
    backgroundPixmap = backgroundPixmap.scaled(WIDTH, HEIGHT, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    setBackgroundBrush(backgroundPixmap);

    auto board = m_game->getRoundHandler()->getBoard();
    // Initialize all the location places
    for (auto& location : board->getLocations())
        createLocationRectItems(location->getLocationPlaces());

    // Create buildingcardsdeckviews and add them to the scene
    auto buildingdecks = board->getBuildingCardsDecks();
    for (int i = 0; i < buildingdecks.length(); ++i) {
        auto buildingCardDeckView{new BuildingCardsDeckView{buildingdecks[i], i}};
        m_buildingCardsDeckViews.append(buildingCardDeckView);
        addItem(buildingCardDeckView);
        createLocationRectItems(buildingdecks[i]->getLocationPlaces());
    }
    // Create the toolRectItems
    ToolMakerLocation* toolmaker = dynamic_cast<ToolMakerLocation*>(board->getLocation("Tool Maker"));
    auto toolDeck{toolmaker->getToolDeck()};
    // Create 2 tool rect items on coordinates (587,397) and (705, 397)
    m_toolRectItems.append(new ToolRectItem(587, 397, 1, toolDeck));
    m_toolRectItems.append(new ToolRectItem(705, 397, 3, toolDeck));
    for (auto& toolRectItem : m_toolRectItems)
        addItem(toolRectItem);

    // Create activecardsview and add them to the scene
    auto activeCards = board->getCivilizationDeck()->getActiveCards();
    for (auto activeCard : activeCards) {
        auto activeCardDeckView{new ActiveCardView{activeCard}};
        m_activeCardViews.append(activeCardDeckView);
        addItem(activeCardDeckView);
        createLocationRectItems(activeCard->getLocationPlaces());
    }
}


/*
 * Create a LocationRectItem for all the given LocationPlaces and add them to the scene
 * @param places: all the locationplaces that need to be added to the scene
*/
void GameScene::createLocationRectItems(const QVector<LocationPlace *> places)
{
    for (auto& locationPlace : places) {
        auto newLocationRectItem{new LocationRectItem{locationPlace}};
        m_locationRectItems.append(newLocationRectItem);
        addItem(newLocationRectItem);
    }
}

