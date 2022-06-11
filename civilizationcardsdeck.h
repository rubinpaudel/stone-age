/* Robert */
#ifndef CIVILIZATIONCARDSDECK_H
#define CIVILIZATIONCARDSDECK_H

#include "location.h"

class CivilizationCard;
class ActiveCivilizationCard;

class CivilizationCardsDeck
{
public:
    CivilizationCardsDeck(QJsonObject deckObject); // Constructor

    void removeFirstCard(); // Remove first card of deck
    bool isEmpty() const; // Check if m_civilizationCards is empty
    void refillActiveCards(); // Refill m_activeCards

    QVector<ActiveCivilizationCard*> getActiveCards() const; // Get active cards

    QJsonObject toJSON() const; // Return a JSON object of the class
    ~CivilizationCardsDeck(); // Destructor
private:
    void initializeCivCards(QJsonArray civilizationCardsArray);
    void shuffleCards();
    void initializeActiveCards(QJsonArray activeCardsArray);

    QVector<CivilizationCard*> m_civilizationCards; // Current looking card deck
    QVector<ActiveCivilizationCard*> m_activeCards; // Active cards on the board
};

#endif // CIVILIZATIONCARDSDECK_H
