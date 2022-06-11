/* Robert */
#ifndef POINTSCIVILIZATIONCARD_H
#define POINTSCIVILIZATIONCARD_H

#include <civilizationcard.h>

class PointsCivilizationCard : public CivilizationCard
{
public:
    PointsCivilizationCard(QJsonObject derivedCardObject); // Constructor

    void applyReward(Player* player) override; // Apply card reward

    QJsonObject toJSON() const override; // Return a JSON object of the class
};

#endif // POINTSCIVILIZATIONCARD_H
