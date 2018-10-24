//
// Created by nnstein on 20/10/18.
//

#ifndef HASHTABLE_THESIS_HASHSLOT_H
#define HASHTABLE_THESIS_HASHSLOT_H


template<class K, class E>
class HashSlot {
    unsigned hash;
    K* key;
    E* element;

public:
    HashSlot();
    HashSlot(unsigned hash, K* key, E* element);
    int get_hash();
    K*   get_key();
    E*   get_element();
    void set_hash(unsigned hash);
    void set_key(K* key);
    void set_element(E* element);
};

#include "HashSlot.tpp"
#endif //HASHTABLE_THESIS_HASHSLOT_H
