#ifndef SSL_TEST_H
#define SSL_TEST_H

#include <QDebug>
#include <QFile>
#include <QDirIterator>
#include <QDir>

#include <openssl/sha.h>

QString sha256_file(QString filePath);


void RunTest()
{
        QDirIterator dirIt("D:\\Projects\\ThirdPartyBuilds\\cmake_builds\\zlib128\\zlib-128\\doc", QDir::AllDirs | QDir::NoDotAndDotDot);
        //dirIt.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);

        /*while (dirIt.hasNext())
        {
            dirIt.next();
            QDir currDir(dirIt.filePath());
            QFileInfoList fileList = currDir.entryInfoList();

            for(int i = 0; i < fileList.size(); i++)
            {
                qDebug() << fileList.at(i).absolutePath();
            }

            qDebug() << dirIt.filePath();
        }*/

        QDir dir("D:\\Projects\\ThirdPartyBuilds\\cmake_builds\\zlib128\\zlib-128\\doc");
        dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);

        QFileInfoList fileList = dir.entryInfoList();

        for(int i = 0; i < fileList.size(); i++)
        {
            qDebug() << fileList[i].filePath();
            qDebug() << "Hash:" << sha256_file(fileList[i].filePath());
            //ReadFile(fileList[i].filePath());
        }
}


QString sha256_file(QString filePath)
{
    char result_buff[65];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();       
        QByteArray ba = line.toLatin1();
        SHA256_Update(&sha256, ba.data(), line.length());
    }

    SHA256_Final(hash, &sha256);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(result_buff + (i * 2), "%02x", hash[i]);
    }

    result_buff[64] = 0;
    QString finalStr = QString::fromUtf8(result_buff);

    file.close();

    return finalStr;
}


#endif // SSL_TEST_H
