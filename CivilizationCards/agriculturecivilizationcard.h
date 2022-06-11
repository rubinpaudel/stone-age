/* Robert */
#ifndef AGRICULTURECIVILIZATIONCARD_H
#define AGRICULTURECIVILIZATIONCARD_H

#include <civilizationcard.h>

class AgricultureCivilizationCard : public CivilizationCard
{
public:
    AgricultureCivilizationCard(QJsonObject derivedCardObject); // Constructor

    void applyReward(Player* player) override; // Apply card reward

    QJsonObject toJSON() const override; // Return a JSON object of the class
};

#endif // AGRICULTURECIVILIZATIONCARD_H
