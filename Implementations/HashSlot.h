//
// Created by nnstein on 20/10/18.
//

#ifndef HASHTABLE_THESIS_HASHSLOT_H
#define HASHTABLE_THESIS_HASHSLOT_H


template<class K, class E>

class HashSlot
{
    int hash;
    K key;
    E element;

public:
    HashSlot(int hash, K key, E element);
    int get_hash();
    K   get_key();
    E   get_element();
};

#include "HashSlot.tpp"
#endif //HASHTABLE_THESIS_HASHSLOT_H
