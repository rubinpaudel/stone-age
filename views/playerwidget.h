/* Robert */
#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

class Player;
class PlayerItem;
class BuildingCardsViewer;
class CivilizationCardsViewer;

class PlayerWidget : public QFrame
{
    Q_OBJECT
public:
    PlayerWidget(Player* player, QWidget* parent = nullptr); // Constructor
signals:
    void cardsButtonPressed(Player* m_player);
public slots:
    void updateScore();
    void updateResources();
    void updateWorker();
    void updateLevel();
    void updateBuildings();
    void updateCards();
    void openBuildingCardsViewer();
    void openCivilizationCardsViewer();
private:
    QHBoxLayout* maketitle();
    QGridLayout* makeGridLayout();

    Player* m_player;
    QLabel* m_scoreLabel;
    QVector<PlayerItem*> m_resourcePlayerItems;
    PlayerItem* m_workerPlayerItem;
    PlayerItem* m_levelPlayerItem;
    QPushButton* m_buildingsButton;
    QPushButton* m_civilizationButton;
    BuildingCardsViewer* m_buildingCardsViewer;
    CivilizationCardsViewer* m_civilizationCardsViewer;
};

#endif // PLAYERWIDGET_H
