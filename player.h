/* Rubin */
#ifndef PLAYER_H
#define PLAYER_H

#include "resource.h"

#include <QJsonObject>
#include <QVector>
#include <QObject>

class Tool;
class BuildingCard;
class CivilizationCard;



class Player : public QObject
{
    Q_OBJECT
public:

    enum class Color { Red, Green, Blue, Yellow};

    Player(QJsonObject playerJSONObject);
    void addScore(int amount); // increase score
    void addWorker(int amount); // increase worker amount
    void addAgricultureLevel(int amount); // increase agriculture level
    void addResource(Resource::ResourceType resourceType, int amount); // increase the amount of a certain resource that the player owns
    void moveWorkers(int amount); // decrements m_availableWorkerAmount
    void addBuildingCard(BuildingCard* card); // add a buildingCard to the deck
    void addCivilizationCard(CivilizationCard* card); // add a civilizationCard to the deck
    void addTool(Tool* tool); // add another tool to the player
    /* Getters */
    QVector<BuildingCard*> getBuildingCards() const; // return all the
    QVector<CivilizationCard*> getCivilizationCards() const;
    Resource* getResource(Resource::ResourceType resourceType) const; // return a resource a player has
    QVector<Resource*> getResources() const; // return all the resources a player has
    int getScore() const; // return the score the player currently has
    int getTotalScore() const; // return the total score (with resources, ..)
    int getTotalWorkerAmount() const; // return the total amount of workers
    int getAvailableWorkerAmount() const; // return the remaining workers
    int getAgricultureLevel() const; // return player's agriculture level
    Player::Color getColor() const; // return the player's color
    QVector<Tool*> getTools(); // return the tools a player has
    QJsonObject toJSON() const; // return a JSON object of the player
    ~Player(); // Destructor
signals:
    void updatedCivilizationCards();
    void updatedScore();
    void updatedResources();
    void updatedBuildings();
    void updatedLevel();
    void updatedWorkers();

private:
    int calculateCivilizationCardsScores() const; // Calculate the scores gained by civilization cards

    int m_totalWorkerAmount;
    int m_availableWorkerAmount;
    int m_agricultureLevel;
    QVector<Resource*> m_resources;
    QVector<BuildingCard*> m_buildingCards;
    QVector<CivilizationCard*> m_civilizationCards;
    Color m_color;
    int m_score;
    QVector<Tool*> m_tools;
};

#endif // PLAYER_H
