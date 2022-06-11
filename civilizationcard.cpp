/* Robert */
#include "civilizationcard.h"
#include "player.h"

CivilizationCard::CivilizationCard(QJsonObject civilizationCardObject)
    :
      m_cardType{static_cast<CardType>(civilizationCardObject.value("cardtype").toInt())},
      m_normalCardAmount{civilizationCardObject.value("normalcardamount").toInt()},
      m_imagePath(civilizationCardObject.value("imagepath").toString())
{}


/*
 * Buy the card by taking subtracting the resources from player
*/
void CivilizationCard::buyCard(Player *player, QVector<Resource *> resources)
{
    for (auto& resource : resources)
        player->addResource(resource->getType(), -resource->getAmount());
}


/*
 * Getter for card type
 * @return m_cardType
*/
CivilizationCard::CardType CivilizationCard::getType() const
{
    return m_cardType;
}


/*
 * Getter for normal card amount
 * @return m_normalCardAmount
*/
int CivilizationCard::getNormalCardAmount() const
{
    return m_normalCardAmount;
}


/*
 * Getter for the card's image path
 * @return m_imagePath
*/
QString CivilizationCard::getImagePath() const
{
    return m_imagePath;
}


/*
 * @return QJsonObject of the class
*/
QJsonObject CivilizationCard::toJSON() const
{
    int cardIndex{static_cast<int>(m_cardType)};
    QJsonObject card{{"cardtype", cardIndex}, {"normalcardamount", m_normalCardAmount},
                     {"imagepath", m_imagePath}};
    return card;
}


CivilizationCard::~CivilizationCard()
{

}
