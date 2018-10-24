//
// Created by nnstein on 20/10/18.
//

#ifndef HASHTABLE_THESIS_HASHTABLE_H
#define HASHTABLE_THESIS_HASHTABLE_H

#include "../Util/enums.h"
#include "../HashFunctions/Hash.h"
#include "../Util/HashSlot.h"

template<class K, class E>
class HashTable {
protected:
    HashTable() = default;
    ~HashTable();
    HashSlot<K,E>**  slots;
    int         numSlots;
    Hash* hash;
    virtual int get_slot(unsigned hash, K* key, HashSlot<K,E>* slotReturn, int* index=nullptr, bool createSlot=false) = 0;
public:
    HashTable(unsigned numSlots, Hash* hash);
    int get_element(K* key, E** element);
    int insert_element(K* key, E* element, bool update=false);
    int remove_element(K* key, E** element);
};
#include "HashTable.tpp"
#endif //HASHTABLE_THESIS_HASHTABLE_H