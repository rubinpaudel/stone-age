/* Robert */
#include "playeritem.h"
#include "player.h"

#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

PlayerItem::PlayerItem(QString picpath, QString item, QString value, QWidget *parent)
    : QWidget(parent)
{
    // Add the item's picture to the horizontal layout
    QHBoxLayout* hbox{new QHBoxLayout};
    QLabel* piclabel = new QLabel;
    piclabel->setPixmap(QPixmap(picpath));
    hbox->addWidget(piclabel);

    // Add the item name to the vertical layout
    QVBoxLayout* vbox{new QVBoxLayout};
    QLabel* itemLabel{new QLabel{item}};
    itemLabel->setObjectName("player-item-title");
    vbox->addWidget(itemLabel);

    m_amountLabel = new QLabel(value);
    vbox->addWidget(m_amountLabel);
    hbox->addLayout(vbox);
    hbox->addStretch();
    setLayout(hbox);
}


/*
 * Set a new value for the player item label
 * @param value: value to set it to
*/
void PlayerItem::changeValue(QString value)
{
    m_amountLabel->setText(value);
}
