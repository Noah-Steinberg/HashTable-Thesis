//
// Created by nnstein on 20/10/18.
//

#ifndef HASHTABLE_THESIS_HASHTABLE_H
#define HASHTABLE_THESIS_HASHTABLE_H

#include "../HashFunctions/HashFunction.h"
#include "../Util/HashSlot.h"

template<class K, class E>
class HashTable {
    HashTable(unsigned int numSlots, HashFunction<K> get_hash);
    HashSlot<K,E>**  slots;
    int         numSlots;
    HashFunction<K> get_hash;
    virtual int find_slot(K key, HashSlot<K,E>* slotReturn, int* index, bool createSlot) = 0;

public:
    int get_element(K key, E* element);
    int insert_element(K key, E element, bool update);
    int remove_element(K key, E* element);
};
#include "HashTable.tpp"
#endif //HASHTABLE_THESIS_HASHTABLE_H