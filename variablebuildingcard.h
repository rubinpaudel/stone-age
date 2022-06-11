/* Robert */
#ifndef VARIABLEBUILDINGCARD_H
#define VARIABLEBUILDINGCARD_H

#include "buildingcard.h"

class VariableBuildingCard : public BuildingCard
{
public:
    VariableBuildingCard(QJsonObject cardObject); // Constructor

    bool isValidPurchase(QVector<Resource *> resources) const override; // Check if valid purchase

    // Getters
    int getDifferentTypes() const;
    int getAmountNeeded() const;

    bool buyCard(Player* player, QVector<Resource*> resources) override; // Buy a card after checking if valid purchase
    int getPoints() const override; // Get the points worth of the card

    QJsonObject toJSON() const override; // Return a JSON object of the variable building card
private:
    void setCardResources(QVector<Resource*> resources); // Set m_resources
    int m_differentTypes; // Different types needed to buy the card
    int m_amountNeeded; // Amount of resources need to buy the card
};

#endif // VARIABLEBUILDINGCARD_H
