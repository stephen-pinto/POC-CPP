#include "test_unit_general.h"
#include "fs_scanner.h"
#include "hash_generator.h"
#include "generatehashform.h"
#include "fs_index_manager.h"

using namespace std;
using namespace fs_handlers;
using namespace fs_crypto;

test_unit_general::test_unit_general()
{
    out = new QTextStream(stdout);
}

void test_unit_general::runtest_Hashing()
{
    QFile resultFile("D:\\Projects\\Hobby\\QtProjects\\build-SftpTransferClient-Desktop_Qt_5_9_1_MinGW_32bit-Debug\\debug\\Result.file");
    resultFile.open(QIODevice::WriteOnly);
    QTextStream outstream(&resultFile);

    fs_scanner scanner;
    hash_generator hasher;

    QTime timer;
    timer.start();

    qDebug() << "\nLoading list of readable files";

    QStringList list = scanner.getAllReadableFilesOf("D:\\Bakups");

    qDebug() << "\nFound " << list.length() << " readable files";

    qDebug() << "\nGenerating hash for all these files";

    foreach (QString file, list)
    {
        outstream << "\n" << hasher.fileHash(file) << " = " << file;
    }

    int seconds = (timer.elapsed() / 1000);

    outstream.flush();
    resultFile.close();

    qDebug() << "Procedure complete in " << seconds << " secs";
}

void test_unit_general::runTest_IndexManager()
{
    testIndexCreationAndSaving();
    //testIndexLoadingAndModif();
}

void test_unit_general::testIndexCreationAndSaving()
{
    fs_scanner scanner;
    fs_index_manager mngr;
    hash_generator hasher;

    QStringList fileList = scanner.getAllReadableFilesOf("D:\\Tors\\The Official UK Top 40 Singles Chart (20.10.2017) (Mp3 320kbps) [Hunter]");

    qDebug() << "Total items: " << fileList.length();
    //qDebug() << "Adding file: " << fileList[0] << " hash: " << hasher.fileHash(fileList[0]);
    //mngr.add("D://Bakups//single_files//ActiveXTestUse.html", "646c20c9ce41c4f7139f2e7bcc6e612f4b960287ebf8101231cc1733365e18ad");

    QTime timer;
    timer.start();

    foreach (QString file, fileList)
    {
        mngr.add(file, hasher.fileHash(file));
    }

    qDebug() << "Took " << (timer.elapsed() / 60000) << " mins to complete hashing for this drive";

    /*
    auto pIntegList = mngr.getListPtr();
    for(size_t i = 0; i < pIntegList->size(); i++)
    {
        auto item = (*pIntegList)[i];
        qDebug() << item->filePath << " --- " << item->hashCode << " --- " << item->fileSize;
    }
    */

    mngr.save("D:\\Test\\result.json");
}

void test_unit_general::testIndexLoadingAndModif()
{
    hash_generator   hasher;
    fs_index_manager mngr;

    mngr.load("D:\\Test\\result.json");
    auto pIntegList = mngr.getListPtr();

    qDebug() << "Loaded " << pIntegList->size() << " items";

    qDebug() << "Changing element" << (*pIntegList)[6]->filePath;
    //mngr.remove((*pIntegList)[5]->filePath);

    qDebug() << "New count " << pIntegList->size() << " items";
    //mngr.setHash(hasher.fileHash(item->filePath));

    for(size_t i = 0; i < pIntegList->size(); i++)
    {
        auto item = (*pIntegList)[i];
        qDebug() << "For file: " << item->filePath;
        qDebug() << "o. hash = " << item->hashCode;
        qDebug() << "n. hash = " << hasher.fileHash(item->filePath);
        qDebug() << "Last modf. = " << item->lastModified.toString(FS_TSTAMP_FORMAT);
        qDebug() << "Actually modf. = " << item->getLastModifiedTStamp().toString(FS_TSTAMP_FORMAT);
        qDebug() << "hasChanged = " << item->hasFileChanged();
        /*if(i == 6)
        {
            mngr.setHash(item->filePath, hasher.fileHash(item->filePath));
            qDebug() << "m. hash = " << item->hashCode;
        }*/
        qDebug() << "size= " << item->fileSize;
        qDebug() << "---------------------------------------------------";
    }
}
