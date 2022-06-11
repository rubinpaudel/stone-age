/* Robert */
#ifndef CIVILIZATIONCARDMODAL_H
#define CIVILIZATIONCARDMODAL_H

#include <QObject>
#include <QDialog>

class Player;
class CivilizationCard;
class ResourcePickerWidget;

class CivilizationCardModal : public QDialog
{
    Q_OBJECT
public:
    // Constructor
    CivilizationCardModal(Player* player, CivilizationCard* civilizationCard, int resourcesNeeded, QWidget* parent = nullptr);
public slots:
    void checkResources(); // Check if resources in pickers are correct
    void buyCard(); // Buy the card and close with Accepted result
    void rejectAndClose(); // Cancel buying of card by closing with Rejected result
    void setResultToTwoAndClose(); // Send '2' as result and close
private:
    void initializeResourcePickers(); // Initialize the resource pickers

    Player* m_player; // Player that is buying the card
    CivilizationCard* m_civilizationCard; // Card to buy
    int m_resourcesNeeded; // Resources needed to buy card
    ResourcePickerWidget* m_resourcePickerWidget; // ResourcePickers made out of QSpinbox
    QPushButton* m_buyButton;

};

#endif // CIVILIZATIONCARDMODAL_H
