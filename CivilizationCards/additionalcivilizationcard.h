/* Robert */
#ifndef ADDITIONALCIVILIZATIONCARD_H
#define ADDITIONALCIVILIZATIONCARD_H

#include <civilizationcard.h>

class AdditionalCivilizationCard : public CivilizationCard
{
public:
    AdditionalCivilizationCard(QJsonObject derivedCardObject); // Constructor

    void setTopCard(CivilizationCard* card); // Set m_topCard
    CivilizationCard* getTopCard() const; // Return m_topCard

    CivilizationCard* takeTopCard(); // Return m_topCard and set nullptr
    void applyReward(Player* player) override; // Apply card reward

    QJsonObject toJSON() const override; // Return a JSON object of the class
    ~AdditionalCivilizationCard(); // Destructor
private:
    CivilizationCard* m_topCard; // Pointer to top card of CivilizationCardDeck
};

#endif // ADDITIONALCIVILIZATIONCARD_H
