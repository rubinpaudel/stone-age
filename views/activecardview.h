/* Rubin */
#ifndef ACTIVECARDVIEW_H
#define ACTIVECARDVIEW_H

#include <QGraphicsRectItem>

class ActiveCivilizationCard;

class ActiveCardView : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    ActiveCardView(ActiveCivilizationCard* card);
public slots:
    void setPixmapImage(); // set the image of the active card
private:
    constexpr static const qreal WIDTH{158}; // Width of the rect item
    constexpr static const qreal HEIGHT{185}; // Height of the rect item

    ActiveCivilizationCard* m_activeCard;
    QGraphicsPixmapItem* m_pixmapItem;
};

#endif // ACTIVECARDVIEW_H
