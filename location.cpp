/* Rubin */
#include "location.h"
#include "locationplace.h"

#include <QJsonArray>

Location::Location(QJsonObject locationObject)
{
    // Initialize member variables with the json object
    m_name = locationObject.value("name").toString();
    m_minWorkers = locationObject.value("minworkers").toInt();
    m_maxWorkers = locationObject.value("maxworkers").toInt();
    // create all the locationplaces
    QJsonArray places = locationObject.value("places").toArray();
    for (int i = 0; i < places.size(); ++i)
        m_places.append(new LocationPlace{places[i].toObject()});
}

bool Location::addWorker(LocationPlace *locationplace, Player *player)
{
    // If the player still has workers and the selected location doesn't have a worker allow the player to place the worker
    if (player->getAvailableWorkerAmount() > 0 && !locationplace->hasWorker()) {
        // Remove a worker from the player
        player->moveWorkers(1);
        // Add a worker to the location
        locationplace->setWorker(player->getColor());
        return true;
    }
    return false;
}


/*
 * Remove all the workers of a given player from all the location places
 * @param player: the player of who we need to remove the workers
*/
void Location::removeWorker(Player* player)
{
    Player::Color playerColor = player->getColor();
    for (int i = 0; i < m_places.length(); ++i)
    {
        // Check if the locationPlace has a worker and the color matches with the player's color
        if (m_places[i]->hasWorker() && m_places[i]->getWorkerColor() == playerColor)
        {
            // Give a worker back to the player
            player->moveWorkers(-1);
            // remove the player from the locationplace
            m_places[i]->removeWorker();
        }

    }
}


/*
 * @return a vector of all the locationplaces the location owns
*/
QVector<LocationPlace*> Location::getLocationPlaces() const
{
    return m_places;
}


/*
 * @return name of the location
*/
QString Location::getName() const
{
    return m_name;
}


/*
 * @return minimum amount of workers allowed
*/
int Location::getMinWorkerAmount() const
{
    return m_minWorkers;
}


/*
 * Find the amount of workers of a player in the location
 *
 * @param player: player of who we need to find the amount of workers
 * @return: amount of workers
*/
int Location::getPlayerWorkerAmount(const Player* player) const
{
    // Check for each location if it has a worker and workers are from the given player
    int workerAmount = 0;
    for (int i = 0; i < m_places.length(); ++i)
        if (m_places[i]->hasWorker() && m_places[i]->getWorkerColor() == player->getColor())
            ++workerAmount;
    return workerAmount;
}


/*
 * @return QJsonObject of the class
*/
QJsonObject Location::toJSON() const
{
    QJsonObject locationObj{{"name", m_name}, {"minworkers", m_minWorkers}, {"maxworkers", m_maxWorkers}};
    // Create a JSON array of locationplace JSON objects
    QJsonArray places;
    for (int i = 0; i < m_places.length(); ++i)
        places.append(m_places[i]->toJSON());
    // Add the locationplaces object array in the location array
    locationObj.insert("places", places);

    return locationObj;
}


Location::~Location()
{
    // delete all the places
    for (auto& place : m_places)
        delete place;
}
