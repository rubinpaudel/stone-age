/* Rubin */
#ifndef BUILDINGCARDMODAL_H
#define BUILDINGCARDMODAL_H
#include <QObject>
#include <QDialog>
#include <QGridLayout>

class ResourcePickerWidget;
class ResourcePicker;
class VariableBuildingCard;
class Player;
class BuildingCardModal : public QDialog
{
    Q_OBJECT
public:
    BuildingCardModal(Player* player, VariableBuildingCard* buildingCard, QWidget* parent = nullptr);
public slots:
    void buyCard();
    void rejectAndClose();
    void setResultToTwoAndClose();
    bool checkResources();
private:
    void initializeResourcePickers();

    Player* m_player;
    VariableBuildingCard* m_buildingCard;
    ResourcePickerWidget* m_resourcePickerWidget;
    QPushButton* m_buyButton;
};

#endif // BUILDINGCARDMODAL_H
