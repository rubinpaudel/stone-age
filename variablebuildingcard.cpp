/* Robert */
#include "variablebuildingcard.h"
#include "resource.h"
#include "player.h"

VariableBuildingCard::VariableBuildingCard(QJsonObject cardObject)
    : BuildingCard{cardObject},
      m_differentTypes{cardObject.value("differenttypes").toInt()},
      m_amountNeeded{cardObject.value("amountneeded").toInt()}
{}


/*
 * Checks if the purchase is valid with the given resources
 * @returns true if it is valid, else false
*/
bool VariableBuildingCard::isValidPurchase(QVector<Resource *> resources) const
{
    int differentTypeCount = 0, totalAmountCount = 0, amount;
    for (int i = 0; i < resources.size(); ++i) {
        amount = resources[i]->getAmount();
        if (amount > 0) {
            ++differentTypeCount;
            totalAmountCount += amount;
        }
    }
    bool valid = differentTypeCount >= m_differentTypes && totalAmountCount == m_amountNeeded;
    if (valid || (getDifferentTypes() == -1 && totalAmountCount <= m_amountNeeded && totalAmountCount >= 1))
        valid = true;

    return valid;
}


/*
 * Getter for m_differentTypes
 * @returns m_differentTypes
*/
int VariableBuildingCard::getDifferentTypes() const
{
    return m_differentTypes;
}


/*
 * Getter for m_amountNeeded
 * @returns m_amountNeeded
*/
int VariableBuildingCard::getAmountNeeded() const
{
    return m_amountNeeded;
}


/*
 * Checks if the purchase is valid with the given resources
 * If so, buy the card and remove resources from that player
 * @returns true if it is purchased, else false
*/
bool VariableBuildingCard::buyCard(Player *player, QVector<Resource *> resources)
{
    if (!isValidPurchase(resources))
        return false;
    for (auto& resource : resources)
        player->addResource(resource->getType(), -resource->getAmount());
    setCardResources(resources);
    return true;
}


/*
 * Calculate the amount of points you get from buying the card and return it
 * @returns amount of points from buying card
*/
int VariableBuildingCard::getPoints() const
{
    int points{0};
    for (auto& resource : m_resources)
        points += (resource->getAmount() * resource->getValue());
    return points;
}


/*
 * @return QJsonObject of the class
*/
QJsonObject VariableBuildingCard::toJSON() const
{
    QJsonObject json{BuildingCard::toJSON()};
    json.insert("differenttypes", m_differentTypes);
    json.insert("amountneeded", m_amountNeeded);
    json.insert("type", 1);
    return json;
}


/*
 * Setter for m_resources
 * @param resources: the resources you want to set it with
*/
void VariableBuildingCard::setCardResources(QVector<Resource *> resources)
{
    for (auto& resource : resources)
        // Make a deep copy of the resource and add it to the cards resources
        m_resources.append(new Resource(*resource));
}
