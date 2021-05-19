#ifndef HASH_GENERATOR_H
#define HASH_GENERATOR_H

#include <QString>

#define TRANSLATE_HASH(result_buff, hash, len) \
    for(int i = 0; i < len; i++)    \
        sprintf(result_buff + (i * 2), "%02x", hash[i])

#define CHUNK_SIZE 4096
#define HASH_STR_LENGTH(digestLength) (digestLength * 2)

namespace fs_crypto {

    class hash_generator
    {

    public:
        hash_generator();

        QString hash_MD5(QString data);

        QString hash(QString data);

        QString hash256(QString data);

        QString fileHash(QString filePath);

        QString fileHash256(QString filePath);

    };
}

#endif // HASH_GENERATOR_H
