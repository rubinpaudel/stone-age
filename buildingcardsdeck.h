/* Rubin */
#ifndef BUILDINGCARDSDECK_H
#define BUILDINGCARDSDECK_H

#include <QVector>
#include "location.h"

class BuildingCard;

class BuildingCardsDeck : public QObject, public Location
{
    Q_OBJECT
public:
    // Constructor
    BuildingCardsDeck(QJsonObject deckObject);

    // Getters
    int getRemainingCards() const;
    BuildingCard* getActiveCard() const; // return the active card

    void next(); // Change the active card
    bool isEmpty() const; // returns if the deck is empty
    void addCard(BuildingCard* card); // add a card to the deck
    void applyReward(Player* player) override; // reward the player the active buildingcard
    QJsonObject toJSON() const override; //  return a JSON object of the deck

    // Destructor
    ~BuildingCardsDeck();
signals:
    void changedActiveCard();
private:
    QVector<BuildingCard*> m_buildingCards;
    int m_activeCardIndex;
};

#endif // BUILDINGCARDSDECK_H
