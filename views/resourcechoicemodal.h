/* Robert */
#ifndef RESOURCECHOICEMODAL_H
#define RESOURCECHOICEMODAL_H

#include <QObject>
#include <QDialog>
#include <QGridLayout>

class ResourcePickerWidget;
class Player;

class ResourceChoiceModal : public QDialog
{
    Q_OBJECT
public:
    ResourceChoiceModal(Player* player, QWidget *parent); // Constructor
public slots:
    void checkResources(); // Check if resources on picker widget are correct
    void acceptButtonClicked(); // Collect reward and close modal
private:
    static const int m_resourceAmount{2};
    void initializeResourcePickers();
    Player* m_player;
    ResourcePickerWidget* m_resourcePickerWidget;
    QPushButton* m_acceptButton;
};

#endif // RESOURCECHOICEMODAL_H
