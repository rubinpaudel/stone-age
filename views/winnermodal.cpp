/* Rubin */
#include "winnermodal.h"
#include "player.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

WinnerModal::WinnerModal(Player *player, QWidget* parent)
    : QDialog{parent}
{
    QString starImg{":/assets/resources/gameassets/star.png"};

    QString titleText{QString("Player %1 has won!").arg(static_cast<int>(player->getColor())+1)};
    auto title{new QLabel{titleText}};
    title->setAlignment(Qt::AlignHCenter);
    // Create a starImage
    auto starImage{new QLabel};
    starImage->setPixmap(QPixmap(starImg).scaled(15,15, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    // Create a lable with the total score of a player
    auto scoreLabel{new QLabel{QString::number(player->getTotalScore())}};
    // Create a layout with the lable and image
    auto scoreLayout{new QHBoxLayout};
    scoreLayout->addWidget(starImage);
    scoreLayout->addWidget(scoreLabel);
    scoreLayout->setAlignment(Qt::AlignHCenter);
    // Create a button to close the dialog
    QPushButton* closeButton{new QPushButton{"Close"}};
    // Create a mainLayout
    auto mainLayout{new QVBoxLayout{}};
    mainLayout->addWidget(title);
    mainLayout->addLayout(scoreLayout);
    mainLayout->addWidget(closeButton);
    setLayout(mainLayout);

    connect(closeButton, &QPushButton::clicked, this, &WinnerModal::closeDialog);
    setAttribute(Qt::WA_DeleteOnClose);
}

void WinnerModal::closeDialog()
{
    close();
}

