/* Rubin */
#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>

class QGraphicsView;
class Game;
class PlayerWidget;
class GameScene;
class RoundStatusBar;

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    GameWidget(Game* game, QWidget *parent = nullptr);
private:
    void initializeWidget();
    Game* m_game;
    GameScene* m_gameScene;
    QVector<PlayerWidget*> m_playerWidgets;
    QGraphicsView* m_gameView;
    RoundStatusBar* m_roundStatusBar;
};

#endif // GAMEWIDGET_H
