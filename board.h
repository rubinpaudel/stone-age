/* Robert */
#ifndef BOARD_H
#define BOARD_H

#include <QJsonObject>
#include <QVector>

class Location;
class BuildingCardsDeck;
class CivilizationCardsDeck;

class Board
{
public:
    Board(QJsonObject boardObject);

    Location* getLocation(QString locationName) const;
    QVector<Location*> getLocations() const;
    QVector<BuildingCardsDeck*> getBuildingCardsDecks() const;
    CivilizationCardsDeck* getCivilizationDeck() const;

    QJsonObject toJSON() const;
    ~Board();
private:
    void createBuildingCardsDeck(QJsonArray buildingCardsObject);
    QVector<Location*> m_locations;
    QVector<BuildingCardsDeck*> m_buildingCards;
    CivilizationCardsDeck* m_civilizationCards;
};

#endif // BOARD_H
