//
// Created by nnstein on 22/10/18.
//

#ifndef HASHTABLE_THESIS_HASHNODE_H
#define HASHTABLE_THESIS_HASHNODE_H


#include "HashSlot.h"

template<class K, class E>
class HashNode {
    HashNode<K,E>* next;
    HashSlot<K,E>* data;

public:
    HashNode();
    HashNode(HashSlot<K,E>* data);
    HashNode(HashNode<K,E>* next, HashSlot<K,E>* data);
    HashNode<K,E>* get_next();
    HashSlot<K,E>* get_data();
    void set_next(HashNode<K,E>* node);
    void set_data(HashSlot<K,E>* data);
};

#include "HashNode.tpp"
#endif //HASHTABLE_THESIS_HASHNODE_H
