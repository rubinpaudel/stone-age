/* Robert */
#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>

class StartScreen;
class Game;
class GameWidget;
class Player;

class GameWindow : public QMainWindow
{
    Q_OBJECT
public:
    GameWindow(QWidget *parent = nullptr); // Constructor
    void closeEvent(QCloseEvent* event) override; // Modified overridden closeEvent
    ~GameWindow(); // Destructor
public slots:
    void startGame(); // Start a default game
    void loadGame(); // Start a game from a load
    void closeApplication(); // Close the application
    void newGame(); // Delete current game and start a new one
    void saveGame(); // Save current game progress
    void showWinnerModal(Player* player); // Open the winner modal
private:
    void initializeStartScreen();
    void initializeGameWidget();
    void createGame(QString path); // Create a game with a chosen path
    void setupMenuBar();

    StartScreen* m_startScreen;
    Game* m_game;
    GameWidget* m_gameWidget;
};

#endif // GAMEWINDOW_H
