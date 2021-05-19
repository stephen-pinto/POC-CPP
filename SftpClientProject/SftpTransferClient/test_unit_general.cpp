#include "test_unit_general.h"
#include "fs_scanner.h"
#include "hash_generator.h"
#include "generatehashform.h"
#include "fs_index_manager.h"

using namespace std;
using namespace fs_handlers;
using namespace sftp_crypto;

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
    testIndexLoadingAndModif();
}

void test_unit_general::testIndexCreationAndSaving()
{
    fs_scanner scanner;
    fs_index_manager mngr;
    hash_generator hasher;

    QStringList list = scanner.getAllReadableFilesOf("D:\\Bakups\\single_files");
    qDebug() << "Total items: " << list.length();

    qDebug() << "Adding file: " << list[0] << " hash: " << hasher.fileHash(list[0]);
    //mngr.add("D://Bakups//single_files//ActiveXTestUse.html", "646c20c9ce41c4f7139f2e7bcc6e612f4b960287ebf8101231cc1733365e18ad");

    foreach (QString file, list)
    {
        mngr.add(file, hasher.fileHash(file));
    }

    auto pIntegList = mngr.getListPtr();
    for(size_t i = 0; i < pIntegList->size(); i++)
    {
        auto item = (*pIntegList)[i];
        qDebug() << item->filePath << " --- " << item->hashCode << " --- " << item->fileSize;
    }

    mngr.save("C:\\Users\\K602\\Desktop\\Output\\result.json");
}

void test_unit_general::testIndexLoadingAndModif()
{

}
