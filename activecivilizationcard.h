/* Robert */
#ifndef ACTIVECIVILIZATIONCARD_H
#define ACTIVECIVILIZATIONCARD_H

#include "location.h"

class CivilizationCard;

class ActiveCivilizationCard : public QObject, public Location
{
    Q_OBJECT
public:
    ActiveCivilizationCard(QJsonObject cardObject);

    void applyReward(Player* player); // Apply reward and give m_civilizationCard to player

    // Getters
    int getResourcesNeeded() const;
    CivilizationCard* getCivilizationCard() const;

    CivilizationCard* takeCivilizationCard(); // Take m_civilizationCard as return value and set on nullptr

    // Setters
    void setCivilizationCard(CivilizationCard* civilizationCard);
    void setResourcesNeeded(int value);

    QJsonObject toJSON() const;
    ~ActiveCivilizationCard();
signals:
    void changedActiveCard();
private:
    int m_resourcesNeeded; // Resources needed to buy the card
    CivilizationCard* m_civilizationCard; // The card to buy
};

#endif // ACTIVECIVILIZATIONCARD_H
