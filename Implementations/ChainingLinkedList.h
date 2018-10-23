//
// Created by nnstein on 20/10/18.
//

#ifndef HASHTABLE_THESIS_CHAININGLINKEDLIST_H
#define HASHTABLE_THESIS_CHAININGLINKEDLIST_H


#include "HashTable.h"
template<class K, class E>
class ChainingLinkedList : HashTable<K,E> {
    int find_slot(K key, HashSlot<K,E> * slotReturn, int* index);
};

#include "ChainingLinkedList.tpp"
#endif //HASHTABLE_THESIS_CHAININGLINKEDLIST_H
