/* Robert */
#include "tool.h"

Tool::Tool(QJsonObject toolObject)
    : m_level{toolObject.value("level").toInt()},
      m_maxLevel{toolObject.value("maxlevel").toInt()},
      m_isOneUse{toolObject.value("isoneuse").toBool()},
      m_used{toolObject.value("used").toBool()}
{}


Tool::Tool(int level, bool isOneUse, bool used)
    : m_level{level}, m_isOneUse{isOneUse}, m_used{used}
{}


/*
 * Getter for m_level
 * @return m_level
*/
int Tool::getLevel() const
{
    return m_level;
}


/*
 * Getter for m_isOneUse
 * @return m_isOneUse
*/
bool Tool::getIsOneUse() const
{
    return m_isOneUse;
}


/*
 * Getter for m_used
 * @return m_used
*/
bool Tool::getUsed() const
{
    return m_used;
}


/*
 * Setter for m_used
 * @param used: boolean value if it's used or not
*/
void Tool::setUsed(bool used)
{
    m_used = used;
}


/*
 * Increment the level of the tool if possible
 * @return true if level was incremented, else false
*/
bool Tool::incrementLevel()
{
    if (m_level == m_maxLevel)
        return false;
    ++m_level;
    return true;
}


/*
 * @return QJsonObject of the class
*/
QJsonObject Tool::toJSON() const
{
    return QJsonObject{
        {"level", m_level},
        {"maxlevel", m_maxLevel},
        {"used", m_used},
        {"isoneuse", m_isOneUse}
    };
}
