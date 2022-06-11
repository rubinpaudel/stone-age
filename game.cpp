/* Robert + Rubin */
#include "game.h"
#include "filehandler.h"
#include "roundhandler.h"
#include <QJsonObject>

Game::Game()
    : m_roundHandler{nullptr}
{}


/* Rubin
 * Save the current game to the given path
 * @param path: path where the JSON document needs to be saved
*/
void Game::save(const QString path)
{
    // Create the gameObject with the roundhandler and board json objects
    QJsonObject gameObj{m_roundHandler->toJSON()};
    // Save to file
    FileHandler::saveToJSON(gameObj, path);
    emit savedGame();
}


/* Rubin
 * Load the game ftom the given path
 * @param path: path of the JSON document with a game object
*/
void Game::load(const QString path)
{
    // Reset the roundhandler and board
    reset();
    // Get the gameobject from the file handler
    auto gameObj{FileHandler::loadFromJSON(path)};
    // Pass the roundhandler object to the roundhandler
    m_roundHandler = new RoundHandler{gameObj};
}


/*
 * Delete the round handler
*/
void Game::reset()
{
    if (m_roundHandler == nullptr)
        delete m_roundHandler;
}


/* Rubin
 * Get the winner from the roundhandler and stop the game
*/
void Game::endGame()
{
    if (m_roundHandler == nullptr)
        return;
    auto winner = m_roundHandler->getWinner();
    emit showWinner(winner);
}

/*
 * Getter for m_roundHandler
 * @return m_roundHandler
*/
RoundHandler* Game::getRoundHandler() const
{
    return m_roundHandler;
}


/* Rubin
 *
*/
Game::~Game()
{
    if (m_roundHandler != nullptr)
        delete m_roundHandler;
}
