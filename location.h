/* Rubin */
#ifndef LOCATION_H
#define LOCATION_H
#include "player.h"

#include <QString>
#include <QVector>
#include <QPair>
#include <QJsonObject>


class LocationPlace;

class Location
{
public:
    // Constructor
    Location(QJsonObject locationObject);

    // Getters
    QString getName() const; // Return the name of the location
    QVector<LocationPlace*> getLocationPlaces() const; // Return all the locationPlaces of a location
    int getMinWorkerAmount() const; // return the minimum amount of workers allowed in the location
    int getPlayerWorkerAmount(const Player *player) const; // Return the amount of workers in the location of a given player

    virtual bool addWorker(LocationPlace* locationplace, Player* player); // add a worker to the location
    virtual void removeWorker(Player* player); // remove all the workers of a given player from the location
    virtual void applyReward(Player* player) = 0; // Reward the player for placing his workers on the location
    virtual QJsonObject toJSON() const; // return a JSON object of the location

    // Destructor
    virtual ~Location();
protected:
    QVector<LocationPlace*> m_places;
    QString m_name;
private:
    int m_minWorkers;
    int m_maxWorkers;

};

#endif // LOCATION_H
