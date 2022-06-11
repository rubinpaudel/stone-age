/* Rubin */
#ifndef RESOURCELOCATIONMODAL_H
#define RESOURCELOCATIONMODAL_H

#include <QDialog>
#include <QLabel>

class QHBoxLayout;
class Player;
class ResourceLocation;
class ToolButton;

class ResourceLocationModal : public QDialog
{
    Q_OBJECT
public:
    ResourceLocationModal(Player* player, ResourceLocation* resourceLocation, QWidget* parent = nullptr);
public slots:
    void confirmButtonPressed();
    void resetButtonPressed();
    void updateInfoMessage();
private:
    QHBoxLayout* createToolButtons(); // Create the tool buttons
    QHBoxLayout *createInfoLayout();
    Player* m_player;
    ResourceLocation* m_resourceLocation;
    QVector<ToolButton*> m_toolButtons;
    QPushButton* m_confirmButton;
    QPushButton* m_resetButton;
    QLabel* m_infoLabel;
};

#endif // RESOURCELOCATIONMODAL_H
