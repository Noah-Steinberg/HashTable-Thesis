//
// Created by nnstein on 13/02/19.
// from: https://create.stephan-brumme.com/fnv-hash/
//

#ifndef HASHTABLE_THESIS_FNV1A_H
#define HASHTABLE_THESIS_FNV1A_H
#include "Hash.h"

template<class K>
class FNV1a: public Hash<K> {
public:
    unsigned seed = 2166136261;
    unsigned prime = 16777619;
    FNV1a() = default;
    unsigned digest(K data){
        unsigned hash = seed;
        unsigned numBytes = sizeof(K);
        const auto* ptr = (const unsigned char*) &data;
        while(numBytes--){
            hash = fnv1a(*ptr++, hash);
        }
        return hash;
    }

    inline unsigned fnv1a(unsigned char oneByte, unsigned hash) {
        return (oneByte ^ hash) * prime;
    }
};

#endif //HASHTABLE_THESIS_FNV1A_H
