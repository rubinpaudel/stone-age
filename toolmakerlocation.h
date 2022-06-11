/* Robert */
#ifndef TOOLMAKERLOCATION_H
#define TOOLMAKERLOCATION_H

#include <location.h>

class ToolDeck;

class ToolMakerLocation : public Location
{
public:
    ToolMakerLocation(QJsonObject toolMakerLocationObject); // Constructor

    void applyReward(Player* player) override; // Apply the reward for the player
    bool addWorker(LocationPlace* locationplace, Player* player) override; // add a worker to the location

    ToolDeck* getToolDeck() const; // Getter for m_toolDeck

    QJsonObject toJSON() const override; // Return a JSON object of the tooldeck
private:
    ToolDeck* m_toolDeck;
};

#endif // TOOLMAKERLOCATION_H
