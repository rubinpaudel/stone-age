/* Rubin */
#include "activecardview.h"
#include "activecivilizationcard.h"
#include "civilizationcard.h"
#include "civilizationcardsdeck.h"

ActiveCardView::ActiveCardView(ActiveCivilizationCard *card)
    : m_activeCard{card}, m_pixmapItem{new QGraphicsPixmapItem}
{
    const qreal Y{520}; // Y Coordinate
    const qreal offsetX{632}; // coordinate of the first item
    const qreal X{(((m_activeCard->getResourcesNeeded() - 4) * -1) * WIDTH) + offsetX}; // x coordinate
    // Set the position of the rect item
    setPos(X,Y);
    m_pixmapItem->setParentItem(this);
    setPixmapImage();
    connect(m_activeCard, &ActiveCivilizationCard::changedActiveCard, this, &ActiveCardView::setPixmapImage);

}

/*
 * Change the current pixmap
*/
void ActiveCardView::setPixmapImage()
{
    QString path{""};
    // if there is an active card then set then get the pixmap image path
    if (m_activeCard->getCivilizationCard() != nullptr)
        path = m_activeCard->getCivilizationCard()->getImagePath();
    // load the pixmap in the graphicspixmap item
    auto pixmap{QPixmap{path}};
    if (!pixmap.isNull())
        m_pixmapItem->setPixmap(pixmap.scaled(WIDTH, HEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    else
        m_pixmapItem->setPixmap(pixmap);
}
