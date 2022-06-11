/* Robert */
#ifndef UNIQUETOOLCIVILIZATIONCARD_H
#define UNIQUETOOLCIVILIZATIONCARD_H

#include <civilizationcard.h>

class Tool;

class UniqueToolCivilizationCard : public CivilizationCard
{
public:
    UniqueToolCivilizationCard(QJsonObject derivedCardObject); // Constructor

    void applyReward(Player* player) override; // Apply card reward

    QJsonObject toJSON() const override; // Return a JSON object of the class
    ~UniqueToolCivilizationCard(); // Destructor
private:
    Tool* m_tool; // One-use tool for reward
};

#endif // UNIQUETOOLCIVILIZATIONCARD_H
