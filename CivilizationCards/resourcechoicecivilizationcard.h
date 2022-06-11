/* Robert */
#ifndef RESOURCECHOICECIVILIZATIONCARD_H
#define RESOURCECHOICECIVILIZATIONCARD_H

#include <civilizationcard.h>

class ResourceChoiceCivilizationCard : public CivilizationCard
{
public:
    ResourceChoiceCivilizationCard(QJsonObject derivedCardObject); // Constructor

    void applyReward(Player* player) override; // Apply card reward

    QJsonObject toJSON() const override; // Return a JSON object of the class
};

#endif // RESOURCECHOICECIVILIZATIONCARD_H
