/* Rubin */
#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QWidget>

class QPushButton;
class QVBoxLayout;

class StartScreen : public QWidget
{
    Q_OBJECT
public:
    StartScreen(QWidget *parent = nullptr);

signals:
    void startButtonPushed();
    void loadButtonPushed();
    void exitButtonPushed();

private:

    QVBoxLayout* createButtonLayout();

    QPushButton* m_startButton;
    QPushButton* m_loadButton;
    QPushButton* m_exitButton;

};

#endif // STARTSCREEN_H
