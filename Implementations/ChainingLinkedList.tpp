//
// Created by nnstein on 20/10/18.
//

#include "ChainingLinkedList.h"

template<class K, class E>
ChainingLinkedList<K,E>::ChainingLinkedList(unsigned numSlots, Hash* hash) {
    this->numSlots = numSlots;
    this->hash = hash;
    this->slots = new HashNode<K,E> *[numSlots];
    for(int i=0;i<numSlots;i++){
        this->slots[i] = new HashNode<K,E>();
    }
}

template<class K, class E>
ChainingLinkedList<K,E>::~ChainingLinkedList() {
    free(this->slots);
}

template<class K, class E>
int ChainingLinkedList<K,E>::get_slot(unsigned hash, K* key, HashSlot<K, E> *slotReturn, int *index, bool insertSlot) {
    HashNode<K,E>* node;
    HashNode<K,E>* newNode;

    hash = hash % this->numSlots;

    node = this->slots[hash];
    if(node->get_data()==nullptr){
        if(insertSlot){
            node->set_data(slotReturn);
        }
        return KEY_NOT_FOUND;
    }

    while(node->get_next()!=nullptr && *(node->get_data()->get_key())!=*key){
        node = node->get_next();
    }
    if(*(node->get_data()->get_key())==*key){
        *slotReturn = *(node->get_data());
        return 0;
    }
    if(insertSlot){
        newNode = (HashNode<K,E>*) malloc(sizeof(HashNode<K,E>));
        newNode->set_data(slotReturn);
        node->set_next(newNode);
    }
    return KEY_NOT_FOUND;

}