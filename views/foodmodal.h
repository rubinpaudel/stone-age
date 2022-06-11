/* Rubin */
#ifndef FOODMODAL_H
#define FOODMODAL_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include "player.h"

class ResourcePickerWidget;
class ResourcePicker;

class FoodModal : public QDialog
{
    Q_OBJECT
public:
    FoodModal(int amountNeeded, Player* player, QWidget* parent = nullptr);
public slots:
    void confirm();
    void cancel();
    void pickedResource();
private:
    void initializeResourcePickers(); // create the resource pickers
    void setAmountLabel(); // Change the amount label
    QPushButton* m_confirmButton;
    QPushButton* m_cancelButton;
    QLabel* m_amountLabel;

    ResourcePickerWidget* m_resourcePickerWidget;

    int m_pickedAmount;
    int m_amountNeeded;
    Player* m_player;
};

#endif // FOODMODAL_H
