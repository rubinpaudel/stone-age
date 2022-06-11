/* Rubin */
#include "tooldeck.h"
#include "tool.h"

ToolDeck::ToolDeck(QVector<Tool*> tools) : m_tools{tools}
{}


/*
 * Checks if there are tools of the given level
 * @param level: level of the tool
 * @return true if there are levels of that type, false if there isn't
*/
bool ToolDeck::hasTools(int level) const
{
    for (auto& tool : m_tools)
        if (tool->getLevel() == level || level + 1 == tool->getLevel())
            return true;
    return false;
}


QVector<Tool *> ToolDeck::getTools() const
{
    return m_tools;
}


/*
 * Gives the tool of the given level
 * @paran level: level
 * @return the index of the tool
*/
int ToolDeck::getToolIndex(int level) const
{
    for (int i = 0; i < m_tools.length(); ++i)
        if (m_tools[i]->getLevel() == level)
            return i;
    return -1;
}


/*
 * Returns the tool at the given index
 * @param index : the index of the tool
 * @return : tool at the given index
*/
Tool* ToolDeck::getAtIndex(int index)
{
    if (index < 0 || index >= m_tools.length())
        return nullptr;
    Tool* tool{m_tools[index]};
    m_tools.remove(index);
    emit updatedTools();
    return tool;
}


/*
 * Add a tool to the Vector of tools
 * @param tool: tool that needs to be added to the list
*/
void ToolDeck::addTool(Tool *tool)
{
    m_tools.append(tool);
    emit updatedTools();
}

ToolDeck::~ToolDeck()
{
    for (auto& tool : m_tools)
        delete tool;
}


