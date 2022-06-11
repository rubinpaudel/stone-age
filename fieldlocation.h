/* Robert */
#ifndef FIELDLOCATION_H
#define FIELDLOCATION_H

#include <location.h>

class FieldLocation : public Location
{
public:
    FieldLocation(QJsonObject fieldLocationObject); // Constructor

    void applyReward(Player* player) override; // Apply the location reward
    bool addWorker(LocationPlace* locationplace, Player* player) override;

    QJsonObject toJSON() const override; // return JSON object of the class
};

#endif // FIELDLOCATION_H
