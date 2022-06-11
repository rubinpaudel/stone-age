/* Robert */
#ifndef RESOURCE_H
#define RESOURCE_H

#include <QJsonObject>
#include <QString>

class Resource
{
public:

    enum class ResourceType{Food, Wood, Brick, Stone, Gold};

    // Constructors
    Resource(QJsonObject resourceObject);
    Resource(int amount, int value, ResourceType type, QString imgUrl);

    // Getters
    ResourceType getType() const;
    int getAmount() const;
    int getValue() const;
    int getTotalValue() const;
    QString getImgPath() const;

    void increaseAmount(int amount); // Increase the amount of the resource

    QJsonObject toJSON() const; // Return a JSON object of the resource
private:
    ResourceType m_resourceType;
    int m_amount;
    int m_value;
    const QString m_imgPath;
};

#endif // RESOURCE_H
