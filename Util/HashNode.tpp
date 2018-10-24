//
// Created by nnstein on 22/10/18.
//

#include "HashNode.h"

template<class K, class E>
HashNode<K,E>::HashNode() {
    this->data = nullptr;
    this->next = nullptr;
}


template<class K, class E>
HashNode<K,E>::HashNode(HashSlot<K, E> *data) {
    this->data = data;
    this->next = nullptr;
}

template<class K, class E>
HashNode<K,E>::HashNode(HashNode<K, E> *next, HashSlot<K, E> *data) {
    this->data = data;
    this->next = next;
}

template<class K, class E>
HashSlot<K,E>* HashNode<K,E>::get_data() {
    return this->data;
}

template<class K, class E>
HashNode<K,E>* HashNode<K,E>::get_next() {
    return this->next;
}

template<class K, class E>
void HashNode<K,E>::set_data(HashSlot<K, E> *data) {
    this->data = data;
}

template<class K, class E>
void HashNode<K,E>::set_next(HashNode<K, E> *node) {
    this->next = node;
}