/* Rubin */
#ifndef WINNERMODAL_H
#define WINNERMODAL_H

#include <QDialog>
#include <QObject>

class Player;

class WinnerModal : public QDialog
{
    Q_OBJECT
public:
    WinnerModal(Player* player, QWidget *parent = nullptr);
public slots:
    void closeDialog();
};

#endif // WINNERMODAL_H
