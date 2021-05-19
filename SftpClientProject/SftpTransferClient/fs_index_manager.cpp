#include "fs_index_manager.h"
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

using namespace std;
using namespace fs_handlers;

fs_index_manager::fs_index_manager()
{

}

void fs_index_manager::add(QString filePath, QString hashCode)
{
    size_t i;

    //First try to look for this path if it already exists
    for(i = 0; i < integrityInfoList.size(); i++)
    {
        if(integrityInfoList[i]->filePath == filePath)
            break;
    }

    //If such item already exist then update that
    if(i < integrityInfoList.size())
    {
        setHash(filePath, hashCode);
    }

    //Else create a new entry
    QFileInfo fileInfo(filePath);    
    p_file_integrity_info info = new file_integrity_info();
    info->filePath = filePath;
    info->hashCode = hashCode;
    info->fileSize = fileInfo.size();
    integrityInfoList.push_back(info);
}

void fs_index_manager::remove(QString filePath)
{
    size_t i;

    //Find the index of the matching filePath
    for(i = 0; i < integrityInfoList.size(); i++)
    {
        if(integrityInfoList[i]->filePath == filePath)
            break;
    }

    //Remove the element at that index
    if(i < integrityInfoList.size())
    {
        integrityInfoList.erase(integrityInfoList.begin() + i);
    }

}

void fs_index_manager::save(QString fileName)
{
    QJsonArray jsonItems;

    for(size_t i = 0; i < integrityInfoList.size(); i++)
    {
        jsonItems.push_back(integrityInfoList[i]->getJsonObject());
    }

    writeToIndexFile(fileName, jsonItems);
}

void fs_index_manager::load(QString indexFName)
{
   //Get value list from the JSON index file
   QJsonArray items = loadIndexFile(indexFName);

   for(int i = 0; i < items.count(); i++)
   {
       p_file_integrity_info info = NULL;

       //For each json value which is a json object
       QJsonObject jsonObj = items.at(i).toObject();

       //Extract values and instantiate object
       if(jsonObj.contains("filePath") && jsonObj["filePath"].isString())
       {
           if(info == NULL)
               info = new file_integrity_info();

           info->filePath = jsonObj["filePath"].toString();

           if(jsonObj.contains("filePath") && jsonObj["filePath"].isString())
               info->hashCode = jsonObj["hashCode"].toString();
       }

       //Add object to the list
       if(info != NULL)
       {
            integrityInfoList.push_back(info);
       }              
   }
}

QString fs_index_manager::getHash(QString filePath)
{
    for(size_t i = 0; i < integrityInfoList.size(); i++)
    {
       if(integrityInfoList[i]->filePath == filePath)
       {
           return integrityInfoList[i]->hashCode;
       }
    }

    return "";
}

QString fs_index_manager::getFile(QString hashCode)
{
    for(size_t i = 0; i < integrityInfoList.size(); i++)
    {
       if(integrityInfoList[i]->hashCode == hashCode)
       {
           return integrityInfoList[i]->filePath;
       }
    }

    return "";
}

void fs_index_manager::setHash(QString filePath, QString hashCode)
{
    for(size_t i = 0; i < integrityInfoList.size(); i++)
    {
       if(integrityInfoList[i]->filePath == filePath)
       {
           integrityInfoList[i]->hashCode = hashCode;
       }
    }
}

std::vector<p_file_integrity_info> *fs_index_manager::getListPtr()
{
    return &integrityInfoList;
}

QJsonArray fs_index_manager::loadIndexFile(QString indexFName)
{
    QJsonArray emptyArray;
    QFile jsonFile;
    jsonFile.setFileName(indexFName);

    if(!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return emptyArray;

    QString jsonContent = jsonFile.readAll();
    jsonFile.close();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonContent.toUtf8());
    auto rootElement = jsonDoc.object();

    //if(!jsonObj.contains("root") || !jsonObj["root"].isString())
    //  return emptyArray;

    return rootElement["index"].toArray();
}

void fs_index_manager::writeToIndexFile(QString indexFName, QJsonArray items)
{
    //Open file in write mode and prepare to write
    QFile jsonFile;
    jsonFile.setFileName(indexFName);

    if(!jsonFile.open(QIODevice::ReadWrite | QIODevice::Text))
        return;

    //Prepare JSON content
    QJsonObject rootObj;
    rootObj.insert("index", items);
    QJsonDocument jsonDoc(rootObj);
    QString jsonContent = jsonDoc.toJson();

    //Write to JSON file
    QTextStream stream(&jsonFile);
    stream << jsonContent;
    stream.flush();
    jsonFile.close();
}

p_file_integrity_info fs_index_manager::findItem(QString filePath)
{
    foreach (p_file_integrity_info info, integrityInfoList)
    {
        if(info->filePath.compare(filePath) == 0)
        {
            return info;
        }
    }

    return NULL;
}
