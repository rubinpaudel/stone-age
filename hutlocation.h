/* Robert */
#ifndef HUTLOCATION_H
#define HUTLOCATION_H

#include <location.h>

class HutLocation : public Location
{
public:
    HutLocation(QJsonObject hutLocationObject); // Constructor

    void applyReward(Player* player) override; // Apply the reward for the player
    bool addWorker(LocationPlace* locationplace, Player* player) override; // add a worker to the location

    QJsonObject toJSON() const override; // Return JSON object of the class

};

#endif // HUTLOCATION_H
