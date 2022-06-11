/* Rubin */
#include "buildingcardsdeckview.h"

#include "buildingcardsdeck.h"
#include "buildingcard.h"

BuildingCardsDeckView::BuildingCardsDeckView(BuildingCardsDeck* cardsDeck, int deckNumber)
    : QGraphicsRectItem{0,0, WIDTH, HEIGHT}, m_cardsDeck{cardsDeck}, m_pixmapItem{new QGraphicsPixmapItem{}}
{
    const qreal Y{590}; // Y Coordinate
    const qreal X_OFFSET{14}; // Space between each view
    const qreal X{(deckNumber * WIDTH) + X_OFFSET}; // x coordinate
    // Set the position of the rect item
    setPos(X,Y);
    m_pixmapItem->setParentItem(this);
    setPixmapImage();
    setAcceptHoverEvents(true);
    connect(m_cardsDeck, &BuildingCardsDeck::changedActiveCard, this, &BuildingCardsDeckView::setPixmapImage);
}

void BuildingCardsDeckView::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    setToolTip(QString("<b>Remaining cards : %1</b>").arg(m_cardsDeck->getRemainingCards()));
    QGraphicsRectItem::hoverEnterEvent(event);
}


/*
 * Set the pixmap of the active card
*/
void BuildingCardsDeckView::setPixmapImage()
{
    QPixmap pix{};
    // if there is no active card then make the pixmap transparent otherwise use the imagpath to create the pixmap
    if (m_cardsDeck->getActiveCard() != nullptr)
        pix.load(m_cardsDeck->getActiveCard()->getImagePath());
    QRectF currentRect = rect();
    m_pixmapItem->setPixmap(pix.scaled(currentRect.width(), currentRect.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}
