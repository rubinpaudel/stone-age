/* Robert */
#ifndef PLAYERITEM_H
#define PLAYERITEM_H

#include <QWidget>
#include <QLabel>

class PlayerItem : public QWidget
{
    Q_OBJECT
public:
    PlayerItem(QString picpath, QString item, QString value, QWidget *parent = nullptr); // Constructor
    void changeValue(QString value); // Set a new value for the player item label
private:
    QLabel* m_amountLabel;
};

#endif // PLAYERITEM_H
