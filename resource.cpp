/* Robert */
#include "resource.h"

Resource::Resource(QJsonObject resourceObject)
    : m_resourceType{static_cast<ResourceType>(resourceObject.value("type").toInt())},
      m_amount{resourceObject.value("amount").toInt()},
      m_value{resourceObject.value("value").toInt()},
      m_imgPath{resourceObject.value("imageurl").toString()}
{}


Resource::Resource(int amount, int value, Resource::ResourceType type, QString imgUrl)
    : m_resourceType{type}, m_amount{amount}, m_value{value}, m_imgPath{imgUrl}
{}


/*
 * Getter for m_resourceType
 * @return m_resourceType
*/
Resource::ResourceType Resource::getType() const
{
    return m_resourceType;
}


/*
 * Getter for m_amount
 * @return m_amount
*/
int Resource::getAmount() const
{
    return m_amount;
}


/*
 * Getter for m_value
 * @return m_value
*/
int Resource::getValue() const
{
    return m_value;
}


/*
 * @returns the total value of all amounts of this resource
*/
int Resource::getTotalValue() const
{
    return m_amount * m_value;
}


/*
 * Getter for m_imgPath
 * @return m_imgPath
*/
QString Resource::getImgPath() const
{
    return m_imgPath;
}


/*
 * Increases the amount of the resource
 * @param amount: the amount you'd want to increase m_amount with
*/
void Resource::increaseAmount(int amount)
{
    m_amount += amount;
}


/*
 * @return QJsonObject of the class
*/
QJsonObject Resource::toJSON() const
{
    return QJsonObject {
        {"value", m_value},
        {"amount", m_amount},
        {"type", static_cast<int>(m_resourceType)},
        {"imageurl", m_imgPath}
    };
}
