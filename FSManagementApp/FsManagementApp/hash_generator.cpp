#include "hash_generator.h"
#include <openssl/sha.h>
#include <openssl/md5.h>
#include <QFile>
#include <QFileInfo>

using namespace fs_crypto;

hash_generator::hash_generator()
{

}

QString hash_generator::hash_MD5(QString data)
{
    const int hashLen = HASH_STR_LENGTH(MD5_DIGEST_LENGTH) + 1;
    char result_buff[hashLen];
    unsigned char digest[MD5_DIGEST_LENGTH];

    QByteArray byteArr = data.toUtf8();

    unsigned char* strData = (unsigned char*)(byteArr.constData());

    MD5(strData, data.length(), (unsigned char*)&digest);

    TRANSLATE_HASH(result_buff, digest, SHA_DIGEST_LENGTH);

    QString genHash = QString::fromUtf8(result_buff);
    return genHash;
}

QString hash_generator::hash(QString data)
{
    const int hashLen = HASH_STR_LENGTH(SHA_DIGEST_LENGTH) + 1;
    char result_buff[hashLen];
    unsigned char digest[SHA_DIGEST_LENGTH];

    //Initialize SHA256 component
    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    //Convert string to byte array
    QByteArray byteArr = data.toUtf8();

    //Perform hashing
    SHA256_Update(&sha256, byteArr.data(), byteArr.size());
    SHA256_Final(digest, &sha256);

    //Convert hash to text
    TRANSLATE_HASH(result_buff, digest, SHA_DIGEST_LENGTH);
    result_buff[hashLen - 1] = 0;

    //Convert c array to QString
    QString genHash = QString::fromUtf8(result_buff);

    return genHash;
}

QString hash_generator::hash256(QString data)
{
    const int hashLen = HASH_STR_LENGTH(SHA256_DIGEST_LENGTH) + 1;
    char result_buff[hashLen];
    unsigned char digest[SHA256_DIGEST_LENGTH];

    //Initialize SHA256 component
    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    //Convert string to byte array
    QByteArray byteArr = data.toUtf8();

    //Perform hashing
    SHA256_Update(&sha256, byteArr.data(), byteArr.size());
    SHA256_Final(digest, &sha256);

    //Convert hash to text
    TRANSLATE_HASH(result_buff, digest, SHA256_DIGEST_LENGTH);
    result_buff[hashLen - 1] = 0;

    //Convert c array to QString
    QString genHash = QString::fromUtf8(result_buff);

    return genHash;
}

QString hash_generator::fileHash(QString filePath)
{
    const int hashLen = HASH_STR_LENGTH(SHA_DIGEST_LENGTH) + 1;
    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly))
        return NULL;

    char result_buff[hashLen];
    unsigned char digest[SHA_DIGEST_LENGTH];

    //Initialize SHA256 component
    SHA_CTX sha256;
    SHA1_Init(&sha256);

    //Read 4KB sized chunks at a time and add to SHA256 component
    while(!file.atEnd())
    {
        QByteArray buffer = file.read(CHUNK_SIZE);
        SHA1_Update(&sha256, buffer.data(), buffer.size());
    }

    //Generate and close the component
    SHA1_Final(digest, &sha256);

    //Convert to text
    TRANSLATE_HASH(result_buff, digest, SHA_DIGEST_LENGTH);
    result_buff[hashLen - 1] = 0;

    //Convert c array to QString
    QString genHash = QString::fromUtf8(result_buff);

    //Close file
    file.close();

    //return hash
    return genHash;
}

QString hash_generator::fileHash256(QString filePath)
{
    const int hashLen = HASH_STR_LENGTH(SHA256_DIGEST_LENGTH) + 1;
    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly))
        return NULL;

    char result_buff[hashLen];
    unsigned char digest[SHA256_DIGEST_LENGTH];

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
    SHA256_Final(digest, &sha256);

    //Convert to text
    TRANSLATE_HASH(result_buff, digest, SHA256_DIGEST_LENGTH);
    result_buff[hashLen - 1] = 0;

    //Convert c array to QString
    QString genHash = QString::fromUtf8(result_buff);

    //Close file
    file.close();

    //return hash
    return genHash;
}
