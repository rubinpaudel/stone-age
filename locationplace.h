/* Rubin */
#ifndef LOCATIONPLACE_H
#define LOCATIONPLACE_H
#include "player.h"
#include <QJsonObject>
#include <QObject>

class LocationPlace : public QObject
{
    Q_OBJECT
public:
    // Constructor
    LocationPlace(QJsonObject locationObject);

    // Getters
    QString getLocationName() const; // returns the name of a location
    int getX() const; // return the x coordinate
    int getY() const; // return the y coordinate
    Player::Color getWorkerColor() const; // return the color of the worker

    // Setter
    void setWorker(Player::Color color); // Add a worker

    void removeWorker(); // remove a worker
    bool hasWorker() const; // returns if it has a worker

    QJsonObject toJSON() const; // return a JSON object of the locationplace

signals:
    void addedWorker(Player::Color color);
    void removedWorker();
private:
    QString m_locationName;
    int m_x;
    int m_y;
    Player::Color m_worker;
    bool m_hasWorker;
};

#endif // LOCATIONPLACE_H
