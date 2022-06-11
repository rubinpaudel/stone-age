/* Robert */
#include "hutlocation.h"

HutLocation::HutLocation(QJsonObject hutLocationObject)
    : Location{hutLocationObject}
{}


/*
 * Add a worker
*/
void HutLocation::applyReward(Player *player)
{
    player->addWorker(1);
}


/* Rubin
 * Allow a player to place a worker if they have less than the maximum workers allowes
 * @param locationplace: the place where the player wants to place a worker
 * @param player: the player that wants to place a worker
*/
bool HutLocation::addWorker(LocationPlace *locationplace, Player *player)
{
    const static int maxLevel{10};

    if (player->getTotalWorkerAmount() >= maxLevel)
        return false;

    return Location::addWorker(locationplace, player);
}


/*
 * @return QJsonObject of the class
*/
QJsonObject HutLocation::toJSON() const
{
    auto obj = Location::toJSON();

    obj.insert("type", "HutLocation");
    return obj;
}
