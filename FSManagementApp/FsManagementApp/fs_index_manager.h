#ifndef FS_INDEX_MANAGER_H
#define FS_INDEX_MANAGER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDateTime>
#include <vector>
#include "common.h"

#define JSON_INDEX_FNAME "fs_index.json"

namespace fs_handlers {

    //Format of data stored in the JSON file
    typedef struct file_integrity_info
    {
        QString filePath;
        QString hashCode;
        qint64  fileSize;
        QDateTime lastModified;

        file_integrity_info()
        {
            fileSize = 0;
        }

        QJsonObject getJsonObject();
        void loadJsonObject(QJsonObject jsonObj);

        static bool validateJsonObject(QJsonObject jsonObj);

        QDateTime getLastModifiedTStamp();
        bool hasFileChanged();

    }*p_file_integrity_info;

    //Manager for index files
    class fs_index_manager
    {
    public:
        fs_index_manager();

        void add(QString filePath, QString hashCode);
        void remove(QString filePath);

        void save(QString fileName);
        void load(QString indexFName);

        QString getHash(QString filePath);
        QString getFile(QString hashCode);

        void    setHash(QString filePath, QString hashCode);

#ifdef DEBUG_MODE
        std::vector<p_file_integrity_info>* getListPtr();
#endif

    private:
        QJsonArray loadIndexFile(QString indexFName);
        void writeToIndexFile(QString indexFName, QJsonArray items);

        p_file_integrity_info findItem(QString filePath);

        std::vector<p_file_integrity_info> integrityInfoList;
    };
}

#endif // FS_INDEX_MANAGER_H
