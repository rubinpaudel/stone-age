/* Rubin */
#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>

class LocationPlace;
class LocationRectItem;
class Player;
class Location;
class Game;
class BuildingCardsDeckView;
class ActiveCardView;
class ToolRectItem;


class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene(Game* game, QObject* parent = nullptr);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
private:
    void initializeScene(); // Create the scene
    void createLocationRectItems(const QVector<LocationPlace*> places); // create LocationRectItems
    Game* m_game;
    LocationRectItem* m_selectedLocation;
    QVector<LocationRectItem*> m_locationRectItems;
    QVector<BuildingCardsDeckView*> m_buildingCardsDeckViews;
    QVector<ActiveCardView*> m_activeCardViews;
    QVector<ToolRectItem*> m_toolRectItems;
};

#endif // GAMESCENE_H
