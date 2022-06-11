/* Rubin */
#ifndef TOOLRECTITEM_H
#define TOOLRECTITEM_H

#include <QGraphicsRectItem>
class ToolDeck;

class ToolRectItem : public QGraphicsRectItem, public QObject
{
public:
    ToolRectItem(int x, int y, int level, ToolDeck* tools, QGraphicsItem* parent = nullptr);
public slots:
    void updatePixmap(); // Update the pixmapItem
private:
    static const int WIDTH{65};
    static const int HEIGHT{57};
    const int m_level; // the type of toolRectItems are shown
    ToolDeck* m_toolDeck;
    QGraphicsPixmapItem* m_pixmapItem;
};

#endif // TOOLRECTITEM_H
