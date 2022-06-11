/* Rubin */
#ifndef LOCATIONRECTITEM_H
#define LOCATIONRECTITEM_H

#include "player.h"

#include <QGraphicsRectItem>
#include <QObject>

class LocationPlace;


class LocationRectItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    LocationRectItem(LocationPlace* location, QGraphicsItem* parent = nullptr);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    LocationPlace* getLocationPlace() const; // return the locationplace
public slots:
    void addPixmap(Player::Color c); // add a workers pixmap
    void removePixmap(); // remove the pixmap
private:
    constexpr static const qreal RECT_SIZE{25};
    LocationPlace* m_locationPlace;
    QGraphicsPixmapItem* m_pixmapItem;
};

#endif // LOCATIONRECTITEM_H
