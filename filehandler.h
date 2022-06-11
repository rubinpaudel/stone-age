/* Rubin */
#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QJsonObject>
#include <QString>

class FileHandler
{
public:
    FileHandler();
    static QJsonObject loadFromJSON(const QString path); // load a json file and return a qjsonobject
    static void saveToJSON(const QJsonObject object, const QString path); // save a qjsonobject to the chosen directory
};

#endif // FILEHANDLER_H
