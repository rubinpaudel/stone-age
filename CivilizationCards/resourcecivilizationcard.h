/* Robert */
#ifndef RESOURCECIVILIZATIONCARD_H
#define RESOURCECIVILIZATIONCARD_H

#include <civilizationcard.h>
#include "resource.h"

class ResourceCivilizationCard : public CivilizationCard
{
public:
    ResourceCivilizationCard(QJsonObject derivedCardObject); // Constructor

    void applyReward(Player* player) override; // Apply card reward

    QJsonObject toJSON() const override; // Return a JSON object of the class
private:
    int m_amount; // amount of resources
    Resource::ResourceType m_type; // type of resource
};

#endif // RESOURCECIVILIZATIONCARD_H
