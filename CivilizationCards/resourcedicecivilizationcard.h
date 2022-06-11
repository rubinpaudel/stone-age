/* Robert */
#ifndef RESOURCEDICECIVILIZATIONCARD_H
#define RESOURCEDICECIVILIZATIONCARD_H

#include "civilizationcard.h"
#include "dice.h"
#include "resource.h"

class ResourceDiceCivilizationCard : public CivilizationCard
{
public:
    ResourceDiceCivilizationCard(QJsonObject derivedCardObject); // Constructor

    void applyReward(Player* player) override; // Apply card reward

    QJsonObject toJSON() const override; // Return a JSON object of the class
private:
    Dice m_dice;
    Resource::ResourceType m_type; // type of resource
    int m_value; // value of resource
};

#endif // RESOURCEDICECIVILIZATIONCARD_H
