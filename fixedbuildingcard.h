/* Robert */
#ifndef FIXEDBUILDINGCARD_H
#define FIXEDBUILDINGCARD_H

#include <buildingcard.h>

class FixedBuildingCard : public BuildingCard
{
public:
    FixedBuildingCard(QJsonObject cardObject); // Constructor

    bool isValidPurchase(QVector<Resource *> resources) const override; // Check if it's a valid purchase
    bool buyCard(Player* player, QVector<Resource*> resources) override; // Buy the card

    void setResources(QVector<Resource*> resources);  // Set m_resources

    QJsonObject toJSON() const override; // Return a JSON object of the class
};

#endif // FIXEDBUILDINGCARD_H
