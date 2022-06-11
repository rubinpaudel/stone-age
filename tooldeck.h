/* Rubin */
#ifndef TOOLDECK_H
#define TOOLDECK_H

#include <QObject>
#include <QVector>


class Tool;

class ToolDeck : public QObject
{
    Q_OBJECT
public:

    // Constructor
    ToolDeck(QVector<Tool*> tools);

    // Getters
    QVector<Tool*> getTools() const; // Return all the tools
    int getToolIndex(int level) const; // Return the index of a tool fron the given index
    Tool* getAtIndex(int index); // Give a tool from the given index and remove it from the list

    bool hasTools(int level) const; // Checks if there are tools left of that type of level
    void addTool(Tool* tool); // Add a tool to the list
    // Destructor
    ~ToolDeck();
signals:
    void updatedTools();
private:
    QVector<Tool*> m_tools;
};

#endif // TOOLDECK_H
