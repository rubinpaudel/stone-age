/* Robert */
#include "fieldlocation.h"

FieldLocation::FieldLocation(QJsonObject fieldLocationObject)
    : Location{fieldLocationObject}
{}


/*
 * Add a agriculture level for the player
*/
void FieldLocation::applyReward(Player* player)
{
    player->addAgricultureLevel(1);
}


/* Rubin
 * Allow a player to place a worker if they have less than the maximum agriculturelevel
 * @param locationplace: the place where the player wants to place a worker
 * @param player: the player that wants to place a worker
*/
bool FieldLocation::addWorker(LocationPlace *locationplace, Player *player)
{
    const static int maxLevel{10};

    if (player->getAgricultureLevel() >= maxLevel)
        return false;

    return Location::addWorker(locationplace, player);
}


/*
 * @return QJsonObject of the class
*/
QJsonObject FieldLocation::toJSON() const
{
    auto obj{Location::toJSON()};

    obj.insert("type", "FieldLocation");
    return obj;
}
