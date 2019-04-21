//
// Created by nnstein on 20/10/18.
//

#ifndef HASHTABLE_THESIS_HASHTABLE_H
#define HASHTABLE_THESIS_HASHTABLE_H

#include "../Util/enums.h"
#include "../HashFunctions/Hash.h"
#include "../Util/HashSlot.h"
#include <vector>
#include <memory>
using namespace std;

template<class K, class E>
class HashTable {
protected:
    HashTable() = default;
    vector<HashSlot<K,E>>  slots;
    int         numSlots;
    int         numElements;
    int         resizeFactor = 5;
    Hash<K>* hash;
    virtual HashSlot<K,E>& get_slot(unsigned , K&, int&) = 0;
    virtual int resize() = 0;

public:
    HashTable(unsigned numSlots, Hash<K>* hash);
    virtual int get_element(K&, E&);
    virtual int insert_element(K&, E&, bool update=false);
    virtual int remove_element(K&);
};

#include "HashTable.tpp"
#endif //HASHTABLE_THESIS_HASHTABLE_H