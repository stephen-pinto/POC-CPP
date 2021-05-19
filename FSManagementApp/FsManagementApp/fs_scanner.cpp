#include "fs_scanner.h"

using namespace fs_handlers;

fs_scanner::fs_scanner()
{

}

fs_scanner::~fs_scanner()
{

}

void mergeToStrList(QStringList &list1, QFileInfoList list2)
{
    if(list2.length() < 1)
        return;

    for(int i = 0; i < list2.length(); i++)
    {
        list1.push_back(list2[i].filePath());
    }

    return;
}

void mergeToStrList(QStringList &list1, QStringList list2)
{
    if(list2.length() < 1)
        return;

    for(int i = 0; i < list2.length(); i++)
    {
        list1.push_back(list2[i]);
    }

    return;
}

QStringList fs_scanner::findFiles(QString rootDirPath, QStringList filter)
{
    QStringList matchedList;

    //First find file in root dir
    mergeToStrList(matchedList, matchFiles(rootDirPath, filter));

    QDirIterator dirIterator(rootDirPath, QDir::AllDirs | QDir::NoDotAndDotDot);

    //Traverse through all the child dirs in this root and try to find matching files
    while(dirIterator.hasNext())
    {
        dirIterator.next();

        //Try to match all the files with the provided filters in this directory
        QStringList matchingFiles = findFiles(dirIterator.filePath(), filter);

        //Add the matched items to the main list
        mergeToStrList(matchedList, matchingFiles);
    }

    return matchedList;
}

QStringList fs_scanner::getAllReadableFilesOf(QString rootDirPath)
{
    QStringList matchedList;

    //First add all the files from the root dir
    mergeToStrList(matchedList, getReadableFiles(rootDirPath));

    QDirIterator dirIterator(rootDirPath, QDir::AllDirs | QDir::NoDotAndDotDot);

    //Traverse through all the child dirs in this root and try to find matching files
    while(dirIterator.hasNext())
    {
        dirIterator.next();

        //Try to match all the files with the provided filters in this directory
        QStringList matchingFiles = getAllReadableFilesOf(dirIterator.filePath());

        //Add the matched items to the main list
        mergeToStrList(matchedList, matchingFiles);
    }

    return matchedList;
}

QFileInfoList fs_scanner::matchFiles(QString dirPath, QStringList filter)
{
    QDir dir(dirPath);

    //Set file name filters
    dir.setNameFilters(filter);

    //Filter out unnecessary files
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);

    QFileInfoList result = dir.entryInfoList();
    return result;
}

QFileInfoList fs_scanner::getReadableFiles(QString dirPath)
{
    QDir dir(dirPath);

    //Filter out unnecessary files
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks | QDir::Readable);

    QFileInfoList result = dir.entryInfoList();
    return result;
}
