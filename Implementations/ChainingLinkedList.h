//
// Created by nnstein on 20/10/18.
//

#ifndef HASHTABLE_THESIS_CHAININGLINKEDLIST_H
#define HASHTABLE_THESIS_CHAININGLINKEDLIST_H


#include "HashTable.h"
#include "../Util/HashNode.h"

template<class K, class E>
class ChainingLinkedList : HashTable<K,E> {
    ChainingLinkedList(unsigned int numSlots, HashFunction<K> get_hash);
    HashNode<K,E>  slots;
    int get_slot(K key, HashSlot<K,E>* slotReturn, int* index, bool createSlot);
};

#include "ChainingLinkedList.tpp"
#endif //HASHTABLE_THESIS_CHAININGLINKEDLIST_H
