/* Rubin */
#include "locationplace.h"

LocationPlace::LocationPlace(QJsonObject locationObject)
{
    m_locationName = locationObject.value("name").toString();
    m_x = locationObject.value("x").toInt();
    m_y = locationObject.value("y").toInt();
    m_hasWorker = locationObject.value("hasWorker").toBool();
    m_worker = static_cast<Player::Color>(locationObject.value("worker").toInt());
}


/*
 * Add a worker
 * @param color: the color of the worker
*/
void LocationPlace::setWorker(Player::Color color)
{
    m_hasWorker = true;
    m_worker = color;
    emit addedWorker(color);
}


/*
 * Remove a worker
*/
void LocationPlace::removeWorker()
{
    m_hasWorker = false;
    emit removedWorker();
}


/*
 * @return x coordinate
*/
int LocationPlace::getX() const
{
    return m_x;
}


/*
 * @return y coordinate
*/
int LocationPlace::getY() const
{
    return m_y;
}


/*
 * @return the color of the worker
*/
Player::Color LocationPlace::getWorkerColor() const
{
    return m_worker;
}


/*
 * Returns the name of the location the locationPlace belongs to
*/
QString LocationPlace::getLocationName() const
{
    return m_locationName;
}


/*
 * Returns if the locationplace has a worker
 * @return true if there is a worker, false if there isn't
*/
bool LocationPlace::hasWorker() const
{
    return m_hasWorker;
}


/*
 * @return QJsonObject of the class
*/
QJsonObject LocationPlace::toJSON() const
{

    auto placeObject {QJsonObject{{"name", m_locationName}, {"x", m_x}, {"y", m_y}}};

    placeObject.insert("hasWorker", m_hasWorker);
    placeObject.insert("worker", static_cast<int>(m_worker));

    return placeObject;
}
