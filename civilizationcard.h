/* Robert */
#ifndef CIVILIZATIONCARD_H
#define CIVILIZATIONCARD_H

#include <QJsonObject>

class Player;
class Resource;

class CivilizationCard
{
public:
    enum class CardType{Healing, Writing, Time, Art, Music, Transport, Pottery, Weaving,
                        Hutbuilder, Farmer, Shaman, Toolmaker};

    virtual void applyReward(Player* player) = 0; // Apply card reward
    void buyCard(Player* player, QVector<Resource*> resources);

    // Getters
    CardType getType() const;
    int getNormalCardAmount() const;
    QString getImagePath() const;

    virtual QJsonObject toJSON() const; // Return a JSON object of the class
    virtual ~CivilizationCard();
protected:
    CivilizationCard(QJsonObject civilizationCardObject); // Constructor
private:
    const CardType m_cardType;
    const int m_normalCardAmount; // Amount of normal card multipliers, is -1 if culture card
    const QString m_imagePath;
};

#endif // CIVILIZATIONCARD_H
