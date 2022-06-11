/* Robert */
#ifndef TOOL_H
#define TOOL_H

#include <QJsonObject>

class Tool
{
public:
    // Constructors
    Tool(QJsonObject toolObject);
    Tool(int level, bool isOneUse=true, bool used=false);

    // Getters
    int getLevel() const;
    bool getIsOneUse() const;
    bool getUsed() const;

    // Setters
    void setUsed(bool used);

    bool incrementLevel();

    QJsonObject toJSON() const; // Return a JSON object of the tool
private:
    int m_level;
    int m_maxLevel;
    const bool m_isOneUse;
    bool m_used;
};

#endif // TOOL_H
