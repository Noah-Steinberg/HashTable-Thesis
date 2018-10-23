//
// Created by nnstein on 22/10/18.
//

#include "HashNode.h"


template<class K, class E>
HashNode::HashNode(HashSlot<K, E> *data) {
    return;
}

template<class K, class E>
HashNode::HashNode(HashNode<K, E> *next, HashSlot<K, E> *data) {
    return;
}

template<class K, class E>
HashSlot<K,E>* HashNode::get_data() {
    return NULL;
}

template<class K, class E>
HashNode<K,E>* HashNode::get_next() {
    return NULL;
}

template<class K, class E>
void HashNode::set_data(HashSlot<K, E> *data) {
    return;
}

template<class K, class E>
void HashNode::set_next(HashNode<K, E> *node) {
    return;
}