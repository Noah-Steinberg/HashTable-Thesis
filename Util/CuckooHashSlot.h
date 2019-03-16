//
// Created by nnstein on 09/02/19.
//

#ifndef HASHTABLE_THESIS_CUCKOOHASHSLOT_H
#define HASHTABLE_THESIS_CUCKOOHASHSLOT_H


#include "HashSlot.h"

template<class K,class E>
class CuckooHashSlot : public HashSlot<K,E> {
    unsigned hash2;

public:
    CuckooHashSlot(unsigned, unsigned, K, E);
    CuckooHashSlot() = default;

    unsigned get_hash2() const;
};

#include "CuckooHashSlot.tpp"
#endif //HASHTABLE_THESIS_CUCKOOHASHSLOT_H
