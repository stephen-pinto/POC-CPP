#ifndef HASH_GENERATOR_H
#define HASH_GENERATOR_H

#include <QString>

#define TRANSLATE_HASH(result_buff, hash, len) \
    for(int i = 0; i < len; i++)    \
        sprintf(result_buff + (i * 2), "%02x", hash[i])

#define CHUNK_SIZE 4096

namespace sftp_crypto {

    class hash_generator
    {

    public:
        hash_generator();

        QString hash(QString data);

        QString fileHash(QString filePath);

    };
}

#endif // HASH_GENERATOR_H
