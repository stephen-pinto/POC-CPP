#include "hash_generator.h"
#include <openssl/sha.h>
#include <QFile>
#include <QFileInfo>

using namespace sftp_crypto;

hash_generator::hash_generator()
{

}

QString hash_generator::hash(QString data)
{
    char result_buff[65];
    unsigned char hash[SHA256_DIGEST_LENGTH];

    //Initialize SHA256 component
    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    //Convert string to byte array
    QByteArray baData = data.toLatin1();

    //Perform hashing
    SHA256_Update(&sha256, baData.data(), baData.size());
    SHA256_Final(hash, &sha256);

    //Convert hash to text
    TRANSLATE_HASH(result_buff, hash, SHA256_DIGEST_LENGTH);
    result_buff[64] = 0;

    //Convert c array to QString
    QString genHash = QString::fromUtf8(result_buff);

    return genHash;
}

QString hash_generator::fileHash(QString filePath)
{
    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly))
        return NULL;

    char result_buff[65];
    unsigned char hash[SHA256_DIGEST_LENGTH];

    //Initialize SHA256 component
    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    //Read 4KB sized chunks at a time and add to SHA256 component
    while(!file.atEnd())
    {
        QByteArray buffer = file.read(CHUNK_SIZE);
        SHA256_Update(&sha256, buffer.data(), buffer.size());
    }

    //Generate and close the component
    SHA256_Final(hash, &sha256);

    //Convert to text
    TRANSLATE_HASH(result_buff, hash, SHA256_DIGEST_LENGTH);
    result_buff[64] = 0;

    //Convert c array to QString
    QString genHash = QString::fromUtf8(result_buff);

    //Close file
    file.close();

    //return hash
    return genHash;
}
