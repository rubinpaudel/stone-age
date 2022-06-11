/* Robert + Rubin */
#include "gamewindow.h"
#include "startscreen.h"
#include "game.h"
#include "gamewidget.h"
#include "winnermodal.h"
#include "player.h"
#include "roundhandler.h"

#include <QDebug>
#include <QMenu>
#include <QMenuBar>
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QFontDatabase>
#include <QTimer>
#include <QCloseEvent>

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent), m_startScreen{nullptr}, m_game{new Game},  m_gameWidget{nullptr}
{
    initializeStartScreen();

    // Set font, window icon and name
    QFontDatabase::addApplicationFont(":/font/resources/fonts/nunito.ttf");
    setWindowIcon(QIcon(":/resources/stone_age_icon.png"));
    setWindowTitle("Stone Age");

    // Setup the styling
    QFile file(":/style.qss");
    if(file.open(QFile::ReadOnly)) {
       QString StyleSheet = QLatin1String(file.readAll());
       qApp->setStyleSheet(StyleSheet);
    }

    setWindowState(Qt::WindowMaximized);
}


/*
 * Modified overridden closeEvent that shows winner before window closes
 * @param: QCloseEvent*
*/
void GameWindow::closeEvent(QCloseEvent *event)
{
    // Show the winner if the game has ended
    if (m_game != nullptr) {
        m_game->endGame();
    }
    QMainWindow::closeEvent(event);
}


/*
 * Close the startscreen and create the game
*/
void GameWindow::startGame()
{
    const QString defaultDirectory{"../Stone_age/Saves/config.json"};
    m_startScreen->close();
    createGame(defaultDirectory);
}


/*
 * Load a game
*/
void GameWindow::loadGame()
{
    const QString defaultLoadDirectory{"../Stone_age/Saves"}; // QDesktopServices::storageLocation(QDesktopServices::HomeLocation)

    // Get the path of the JSON file
    QString path{QFileDialog::getOpenFileName(this, tr("Load Game"), defaultLoadDirectory, tr("JSON file (*.json)"))};

    // If there is no path chosen do nothing
    if (path.isEmpty())
        return;
    if (m_gameWidget) // If there is already an old gameWidget remove it and initialize it again
        delete m_gameWidget;

    createGame(path);
}


/*
 * Close the application
*/
void GameWindow::closeApplication()
{
    close();
}


/*
 * Create a message box to warn, if accepted create a new game
*/
void GameWindow::newGame()
{
    // Create warning message box
    QMessageBox::StandardButton reply{QMessageBox::question(this, "Warning",
        "Are you sure you want to start a new game?\nCurrent progress will be lost.",
        QMessageBox::Yes | QMessageBox::No)};

    // Return if user clicked 'No'
    if (reply != QMessageBox::Yes)
        return;

    // Create new game
    const QString defaultDirectory{"../Stone_age/Saves/config.json"};
    if (m_gameWidget) // If there is already an old gameWidget remove it and initialize it again
        delete m_gameWidget;
    createGame(defaultDirectory);
}


/* Rubin
 * Save the game to the disk
*/
void GameWindow::saveGame()
{
    const QString defaultSaveDirectory{"../Stone_age/Saves"}; // QDesktopServices::storageLocation(QDesktopServices::HomeLocation)
    // Open a File Dialog and get the directory
    QString path{QFileDialog::getSaveFileName(this, tr("Save Game"), defaultSaveDirectory, tr("JSON file (*.json)"))};
    if (!path.isEmpty()) {
        m_game->save(path);
        // Show a messagBox
        QMessageBox saveMessageBox{QMessageBox::Information, "Saved Game", "The game has been saved at the specified path!", QMessageBox::Ok, this};
        saveMessageBox.exec();
    }
}


/* Rubin
 * Show a dialog with the winner
*/
void GameWindow::showWinnerModal(Player* player)
{
    auto modal{new WinnerModal{player}};
    modal->exec();
    // Close the window
    // Remove the game and close the window
    delete m_game;
    m_game = nullptr;
    close();
}


/*
 * Initialize the startscreen and connect buttons with functions
*/
void GameWindow::initializeStartScreen()
{
    // Create startscreen and setCentralWidget
    m_startScreen = new StartScreen;
    setCentralWidget(m_startScreen);

    // Connect Buttons
    connect(m_startScreen, &StartScreen::startButtonPushed, this, &GameWindow::startGame);
    connect(m_startScreen, &StartScreen::loadButtonPushed, this, &GameWindow::loadGame);
    connect(m_startScreen, &StartScreen::exitButtonPushed, this, &GameWindow::closeApplication);
}


/*
 * Initialize GameWidget and connect with showWinnerModal() slot
*/
void GameWindow::initializeGameWidget()
{
    // Create game widget and setCentralWidget
    m_gameWidget = new GameWidget{m_game};
    setCentralWidget(m_gameWidget);

    // Fix size and fullscreen
    m_gameWidget->setFixedSize(size().width(), size().height() - menuBar()->size().height());
    showFullScreen();

    // Connect with showWinnerModal() slot
    connect(m_game->getRoundHandler(), &RoundHandler::gameEnded, this, &GameWindow::showWinnerModal);
    connect(m_game, &Game::showWinner, this, &GameWindow::showWinnerModal);
}


/*
 * Delete the old game, setup the menu bar and create a game with the chosen path
 * @param path: path to create a game from
*/
void GameWindow::createGame(QString path)
{
    // Delete old game (if exists) and makes a new one
    delete m_game;
    m_game = new Game{};

    setupMenuBar();

    // Load the game
    m_game->load(path);

    initializeGameWidget();
}


/*
 * Setup the menu bar
*/
void GameWindow::setupMenuBar()
{
    // Create menu
    menuBar()->clear();
    QMenu *menu = menuBar()->addMenu(tr("&File"));

    // Add actions to menu
    menu->addAction(QIcon(":icons/resources/new.png"), tr("New Game"), this, &GameWindow::newGame);
    menu->addAction(QIcon(":icons/resources/save.png"), tr("Save Game"), this, &GameWindow::saveGame);
    menu->addAction(QIcon(":icons/resources/load.png"), tr("Load Game"), this, &GameWindow::loadGame);
    menu->addAction(QIcon(":icons/resources/quit.png"), tr("Quit Game"), this, &GameWindow::closeApplication);
}


GameWindow::~GameWindow()
{
    delete m_game;
}
