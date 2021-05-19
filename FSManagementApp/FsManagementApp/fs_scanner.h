#ifndef FS_SCANNER_H
#define FS_SCANNER_H

#include <vector>
#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QDirIterator>

namespace fs_handlers {

using namespace std;

    class fs_scanner
    {
    public:

        fs_scanner();
        ~fs_scanner();

        QStringList findFiles(QString rootDirPath, QStringList filter);
        QStringList getAllReadableFilesOf(QString rootDirPath);

    private:

        QFileInfoList matchFiles(QString dir, QStringList filter);
        QFileInfoList getReadableFiles(QString dirPath);
    };

}

#endif // FS_SCANNER_H
