/* Rubin */
#ifndef ROUNDSTATUSBAR_H
#define ROUNDSTATUSBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class Player;
class BuildingCardsDeck;
class ActiveCivilizationCard;
class ResourceLocation;
class RoundHandler;
class ItemDiceModal;

class RoundStatusBar : public QFrame
{
    Q_OBJECT
public:
    RoundStatusBar(RoundHandler* roundHandler,QWidget *parent = nullptr);
public slots:
    void cancelTurn();
    void confirmTurn();
    void updateLabel();
    void openFoodModal(int amount);
    void openResourceLocationModal(ResourceLocation* location);
    bool openBuildingCardModal(BuildingCardsDeck* buildingCardsDeck);
    bool openCivilizationCardModal(ActiveCivilizationCard* activeCard);
    void checkActiveModals(Player* player);
private:
    void enableButtons(bool show = true);
    RoundHandler* m_roundHandler;
    QLabel*  m_label;
    QPushButton* m_cancelButton;
    QPushButton* m_confirmButton;
    QVector<ItemDiceModal*> m_activeModals;
};

#endif // ROUNDSTATUSBAR_H
