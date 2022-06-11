/* Rubin */
#include "gamewidget.h"
#include "game.h"
#include "gamescene.h"
#include "view_config.h"
#include "roundstatusbar.h"
#include "roundhandler.h"
#include "player.h"
#include "playerwidget.h"
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QVBoxLayout>


GameWidget::GameWidget(Game* game, QWidget *parent)
    : QWidget(parent), m_game{game}
{
    initializeWidget();
}

/*
 * Create the widget
*/
void GameWidget::initializeWidget()
{
    const qreal HEIGHT{722}, WIDTH{1282};

    /* Create the GameScene without roundHandler and board methods need to be implemented*/
    m_gameScene = new GameScene{m_game};

    /* create a GraphicsView with a fixedSize */
    m_gameView = new QGraphicsView{m_gameScene};
    m_gameView->setFixedSize(WIDTH, HEIGHT);
    // Create the roundStatusbar
    m_roundStatusBar = new RoundStatusBar{m_game->getRoundHandler()};
    // Add the widgets to the main layout
    auto leftSideLayout = new QVBoxLayout;
    auto mainLayout = new QHBoxLayout;
    leftSideLayout->addStretch();
    leftSideLayout->addWidget(m_roundStatusBar);
    leftSideLayout->addSpacing(5);
    leftSideLayout->addWidget(m_gameView);
    leftSideLayout->addStretch();
    mainLayout->addLayout(leftSideLayout);

    auto* playerLayout{new QVBoxLayout};
    for (auto& player : m_game->getRoundHandler()->getPlayers()) {
        auto playerWidget{new PlayerWidget{player, this}};
        playerLayout->addWidget(playerWidget);
    }
    mainLayout->addLayout(playerLayout);
    // Set the layout for the widget
    setLayout(mainLayout);
}


