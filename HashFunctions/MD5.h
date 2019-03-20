//
// Created by nnstein on 20/03/19.
//

#ifndef HASHTABLE_THESIS_MD5_H
#define HASHTABLE_THESIS_MD5_H
#include "Hash.h"
#include "md5_helper.h"

template<class K>
class MD5: public Hash<K> {
public:
    MD5() = default;
    unsigned digest(K data){
        unsigned numBytes = sizeof(K);
        const auto* ptr = (const unsigned char*) &data;
        auto helper = MD5_Helper();
        helper.update(ptr, numBytes);
        helper.finalize();
        return helper.unsigneddigest();
    }
};
#endif //HASHTABLE_THESIS_MD5_H
