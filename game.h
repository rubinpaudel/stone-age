/* Robert */
#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QString>

class RoundHandler;
class Player;

class Game : public QObject
{
    Q_OBJECT
public:
    Game(); // Constructor

    void save(const QString path); // Save game to given path
    void load(const QString path); // Load game from given path
    void reset(); // Delete m_roundHandler
    void endGame();

    RoundHandler* getRoundHandler() const; // Getter for m_roundHandler

    ~Game(); // Destructor
signals:
    void showWinner(Player* player);
    void savedGame();
private:
    RoundHandler* m_roundHandler;
};

#endif // GAME_H
