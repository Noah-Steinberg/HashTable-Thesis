//
// Created by nnstein on 20/10/18.
//

#ifndef HASHTABLE_THESIS_HASHTABLE_H
#define HASHTABLE_THESIS_HASHTABLE_H

#include "../HashFunctions/HashFunction.h"
#include "HashSlot.h"

template<typename K, typename E>
class HashTable
{
    HashTable() = default;
    HashSlot<K,E>**  slots;
    int         numSlots;
    HashFunction<K> get_hash;
    virtual int find_slot(K key, HashSlot<K,E>* slotReturn, int* index) = 0;

public:
    int get_element(K key, E* element);
    int insert_element(K key, E element, bool update);
    int remove_element(K key, E* element);
};
#include "HashTable.tpp"
#endif //HASHTABLE_THESIS_HASHTABLE_H