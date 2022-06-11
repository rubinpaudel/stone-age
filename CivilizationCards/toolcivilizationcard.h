/* Robert */
#ifndef TOOLCIVILIZATIONCARD_H
#define TOOLCIVILIZATIONCARD_H

#include <civilizationcard.h>

class ToolCivilizationCard : public CivilizationCard
{
public:
    ToolCivilizationCard(QJsonObject derivedCardObject); // Constructor

    void applyReward(Player* player) override; // Apply card reward

    QJsonObject toJSON() const override; // Return a JSON object of the class
};

#endif // TOOLCIVILIZATIONCARD_H
