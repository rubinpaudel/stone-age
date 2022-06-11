/* Rubin */
#include "filehandler.h"

#include <QFile>
#include <QJsonParseError>

FileHandler::FileHandler()
{
}


/*
 * Load a JSON file from a give path and return a QJsonObject
 * @param path: path where the file is located
 * @return the root object of the given file in a QJsonObject
*/
QJsonObject FileHandler::loadFromJSON(const QString path)
{
    // get the file from the given path
    QFile file{path};
    // Open the file
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    // Create a byte array and close the file
    QByteArray data = file.readAll();
    file.close();
    // Create a new QJsonDocument with the byte array and the parse error
    QJsonParseError parseError;
    QJsonDocument document = QJsonDocument::fromJson(data, &parseError);
    // if the document is null then the parsing failed, return an empty object
    if (document.isNull())
        return QJsonObject{};
    // return the root object of the json file
    return document.object();
}


/*
 * Save a QJsonObject to the given directory
 * @param object: the root object that needs to be saved in the json file
 * @param path: the path where the file needs to be saved
*/
void FileHandler::saveToJSON(const QJsonObject object, const QString path)
{
    // Create a new file in the given path
    QFile file{path};
    // Open the file to write data
    file.open(QIODevice::WriteOnly);
    // Create the QJsonDocument with the gice given object
    QJsonDocument document{object};
    // Write to the file and close it
    file.write(document.toJson());
    file.close();
}
