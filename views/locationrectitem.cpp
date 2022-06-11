/* Rubin */
#include "locationrectitem.h"
#include "view_config.h"
#include "locationplace.h"

#include <QBrush>
#include <QPen>
#include <QApplication>
#include <QStyleOptionGraphicsItem>


LocationRectItem::LocationRectItem(LocationPlace* location, QGraphicsItem* parent)
    : QGraphicsRectItem{0,0, RECT_SIZE, RECT_SIZE, parent}, m_locationPlace{location}, m_pixmapItem{new QGraphicsPixmapItem}
{
    /* Place the rect item in the correct position */
    setPos(m_locationPlace->getX(), m_locationPlace->getY());
    setZValue(1);
    /* make the rectItem transparent */
    setBrush(Qt::transparent);
    setPen(Qt::NoPen);

    setFlag(ItemIsSelectable);
    setAcceptHoverEvents(true);
    m_pixmapItem->setParentItem(this);

    if (m_locationPlace->hasWorker())
        addPixmap(m_locationPlace->getWorkerColor());
    connect(m_locationPlace, &LocationPlace::addedWorker, this, &LocationRectItem::addPixmap);
    connect(m_locationPlace, &LocationPlace::removedWorker, this, &LocationRectItem::removePixmap);
}


/*
 * Add the pixmap of the worker
 * @param color: color of the worker
*/
void LocationRectItem::addPixmap(Player::Color color)
{
    /* Scale the pixmap item to the size of the rect Item */
    qreal w = rect().width();
    qreal h = rect().height();
    /* Get the path of the workers color */
    QString workerImgPath{QString(":/assets/resources/gameassets/worker%1.png").arg(static_cast<int>(color))};
    QPixmap pixmap{workerImgPath};
    m_pixmapItem->setPixmap(pixmap.scaled(w,h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}


/*
 * Remove pixmap, Make the the rectitem transparent
*/
void LocationRectItem::removePixmap()
{
    QPixmap pixmap{};
    m_pixmapItem->setPixmap(pixmap);
}


/*
 * @return the locationplace the rectItem corresponds to
*/
LocationPlace* LocationRectItem::getLocationPlace() const
{
    return m_locationPlace;
}


/*
 * Change the cursor on hover enter
*/
void LocationRectItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsRectItem::hoverEnterEvent(event);
    QApplication::setOverrideCursor(Qt::PointingHandCursor);
}


/*
 * Change the cursor on hover leave
*/
void LocationRectItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsRectItem::hoverLeaveEvent(event);
    QApplication::setOverrideCursor(Qt::ArrowCursor);
}

/*
 * Reimplementation of the paint method to remove the dotted line around the item
*/
void LocationRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QStyleOptionGraphicsItem* styleOption = const_cast<QStyleOptionGraphicsItem*>(option);
    styleOption->state &= ~QStyle::State_Selected;
    QGraphicsRectItem::paint(painter, styleOption, widget);
}
