/* Robert */
#include "fixedbuildingcard.h"
#include "resource.h"
#include "player.h"
#include <QJsonArray>

FixedBuildingCard::FixedBuildingCard(QJsonObject cardObject)
    : BuildingCard{cardObject}
{}


/*
 * Check if it's a valid purchase with the given amount of resources
 * @return true if it's a valid purchase, else false
*/
bool FixedBuildingCard::isValidPurchase(QVector<Resource *> resources) const
{
    bool hasResource;
    for (int i = 0; i < m_resources.size(); ++i) {
        hasResource = false;
        for (int j = 0; j < resources.size(); ++j) {
            if (resources[j]->getType() == m_resources[i]->getType()) {
                if (resources[j]->getAmount() >= m_resources[i]->getAmount())
                    hasResource = true;
                break;
            }
        }
        if (!hasResource)
            return false;
    }
    return true;
}


/* Rubin
 * If the player is able to buy the card, buy the card and subtract the resources from the player
 * @param player: player that wants to buy the card
 * @return true if the player has bought the card, false if the player hasn't
*/
bool FixedBuildingCard::buyCard(Player *player, QVector<Resource*> resources)
{
    if (!isValidPurchase(resources))
        return false;
    for (auto& resource : m_resources) {
        for (auto& givenResource : resources)
            if (resource->getType() == givenResource->getType()) {
                player->addResource(resource->getType(), -resource->getAmount());
            }
    }
    return true;
}


/*
 * Setter for m_resources
 * @param resources: the resources you want to set it to
*/
void FixedBuildingCard::setResources(QVector<Resource*> resources)
{
    for (auto& resource : resources)
        // Make a deep copy of the resource and add it to the cards resources
        m_resources.append(new Resource(*resource));
}


/*
 * @return QJsonObject of the class
*/
QJsonObject FixedBuildingCard::toJSON() const
{
    auto obj{BuildingCard::toJSON()};
    obj.insert("type", 0);
    return obj;
}
