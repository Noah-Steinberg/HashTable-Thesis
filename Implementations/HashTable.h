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
    Hash<K> hash;
    virtual int get_slot(unsigned , K&, HashSlot<K,E>&, bool) = 0;
public:
    HashTable(unsigned numSlots, Hash<K> hash);
    int get_element(K&, E&);
    int insert_element(K&, E&, bool update=false);
    int remove_element(K&);
};

#include "HashTable.tpp"
#endif //HASHTABLE_THESIS_HASHTABLE_H