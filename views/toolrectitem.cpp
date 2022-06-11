/* Rubin */
#include "toolrectitem.h"
#include "tooldeck.h"

ToolRectItem::ToolRectItem(int x, int y, int level, ToolDeck* tools, QGraphicsItem *parent)
    : QGraphicsRectItem{0, 0, WIDTH, HEIGHT, parent}, m_level{level}, m_toolDeck{tools}
{
    setPos(x, y);
    m_pixmapItem = new QGraphicsPixmapItem{this};
    updatePixmap();

    setFlag(ItemIsSelectable, false);
}


/*
 * Checks if there are tools left if so it adds the pixmap of the tool
 * If there are no tools it doesn't change the pixmap
*/
void ToolRectItem::updatePixmap() {
    //
    if (!m_toolDeck->hasTools(m_level)) {
        // Make tool transparent
        m_pixmapItem->setPixmap(QPixmap{});
    } else {
        // Set the tool image
        QPixmap image{QString(":/assets/resources/gameassets/toolLevel%1.jpg").arg(m_level)};
        m_pixmapItem->setPixmap(image.scaled(WIDTH, HEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }

}
