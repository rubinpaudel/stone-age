/* Rubin */
#ifndef BUILDINGCARDSDECKVIEW_H
#define BUILDINGCARDSDECKVIEW_H

#include <QGraphicsRectItem>

class BuildingCardsDeck;

class BuildingCardsDeckView : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    BuildingCardsDeckView(BuildingCardsDeck* cardsDeck, int deckNumber);
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
public slots:
    void setPixmapImage(); // set the image of the active card
private:
    constexpr static const qreal WIDTH{140}; // Width of the rect item
    constexpr static const qreal HEIGHT{108}; // Height of the rect item

    BuildingCardsDeck* m_cardsDeck;
    QGraphicsPixmapItem* m_pixmapItem;
};

#endif // BUILDINGCARDSDECKVIEW_H
