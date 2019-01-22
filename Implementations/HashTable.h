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

template<class K, class E>
class HashTable {
protected:
    HashTable() = default;
    vector<HashSlot<K,E>>  slots;
    int         numSlots;
    Hash<K> hash;
    virtual int get_slot(unsigned hash, const K &key, HashSlot<K,E> &slotReturn,
            std::unique_ptr<int> index, bool createSlot) = 0;
public:
    HashTable(unsigned numSlots, Hash<K> hash);
    int get_element(const K &key, std::unique_ptr<E> &element);
    int insert_element(const K &key, const E &element, bool update=false);
    int remove_element(const K &key);
};

#include "HashTable.tpp"
#endif //HASHTABLE_THESIS_HASHTABLE_H