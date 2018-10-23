//
// Created by nnstein on 20/10/18.
//

#include "ChainingLinkedList.h"

template<class K, class E>
ChainingLinkedList::ChainingLinkedList(unsigned int numSlots, HashFunction<K> get_hash) {
    this->numSlots = numSlots;
    this->get_hash = get_hash;
    this->slots = malloc(sizeof(HashSlot**) * numSlots);
}

template<class K, class E>
ChainingLinkedList::~ChainingLinkedList() {
    free(this->slots);
}

template<class K, class E>
int ChainingLinkedList<K,E>::get_slot(K key, HashSlot<K, E> *slotReturn, int *index, bool createSlot) {
    unsigned int hash;
    hash = this->get_hash(key);
    hash = hash % numSlots;

}