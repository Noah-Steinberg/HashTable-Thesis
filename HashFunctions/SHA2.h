//
// Created by nnstein on 20/03/19.
//

#ifndef HASHTABLE_THESIS_SHA2_H
#define HASHTABLE_THESIS_SHA2_H
#include "Hash.h"
#include "sha2_helper.h"

template<class K>
class SHA2: public Hash<K> {
public:
    SHA2() = default;
    unsigned digest(K data){
        unsigned numBytes = sizeof(K);
        auto* ptr = (unsigned char*) &data;
        return sha256(ptr, numBytes);
    }
};
#endif //HASHTABLE_THESIS_SHA2_H
