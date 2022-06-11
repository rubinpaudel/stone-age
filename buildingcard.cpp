/* Rubin */
#include "buildingcard.h"
#include "player.h"
#include "resource.h"

#include <QJsonArray>

BuildingCard::BuildingCard(QJsonObject buildingCardObject)
    : m_points{buildingCardObject.value("points").toInt()},
      m_imagePath{buildingCardObject.value("imagepath").toString()}
{
    QJsonArray resources = buildingCardObject.value("resources").toArray();
    for (int i = 0; i < resources.size(); ++i)
        m_resources.append(new Resource{resources[i].toObject()});

}


/*
 * @return amount of point the buildingcard is worth
*/
int BuildingCard::getPoints() const
{
    return m_points;
}


/*
 * @return resources used to buy the card
*/
QVector<Resource*> BuildingCard::getResources() const
{
    return m_resources;
}


/*
 * @return path to the image of the buildingcard
*/
QString BuildingCard::getImagePath() const
{
    return m_imagePath;
}


/*
 * @return QJsonObject of the class
*/
QJsonObject BuildingCard::toJSON() const
{

    QJsonObject cardObj{{"points", m_points}, {"imagepath", m_imagePath}};
    QJsonArray resources;
    for (int i = 0; i < m_resources.length(); ++i)
        resources.append(m_resources[i]->toJSON());
    cardObj.insert("resources", resources);
    return cardObj;
}


BuildingCard::~BuildingCard()
{
    for (auto& resource: m_resources)
        delete resource;
}
