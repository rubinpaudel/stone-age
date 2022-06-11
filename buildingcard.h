/* Rubin */
#ifndef BUILDINGCARD_H
#define BUILDINGCARD_H


#include <QJsonObject>
#include <QVector>

class Resource;
class Player;

class BuildingCard
{
public:

    // Getters
    QVector<Resource*> getResources() const; // return the resources that have been used to buy the card
    QString getImagePath() const; // return the imagepath of the card
    virtual int getPoints() const; // Return the points of the card

    virtual bool buyCard(Player* player, QVector<Resource*> resources) = 0;
    virtual bool isValidPurchase(QVector<Resource*> resources) const = 0; // check if a player can buy the card
    virtual QJsonObject toJSON() const; // return a JSON object of the card

    // Destructor
    virtual ~BuildingCard();
protected:
    // Constructor
    BuildingCard(QJsonObject buildingCardObject);
    QVector<Resource*> m_resources;
    int m_points;
private:
    const QString m_imagePath;
};

#endif // BUILDINGCARD_H
