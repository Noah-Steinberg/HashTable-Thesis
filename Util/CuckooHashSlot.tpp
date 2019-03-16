//
// Created by nnstein on 09/02/19.
//

#include "CuckooHashSlot.h"
template<class K, class E>
CuckooHashSlot<K,E>::CuckooHashSlot(unsigned hash, unsigned hash2, K key, E element)  {
    this->hash = hash;
    this->hash2 = hash2;
    this->key = key;
    this->element = element;
    this->active = true;
    this->empty = false;
};

template<class K, class E>
unsigned CuckooHashSlot<K,E>::get_hash2() const {
    return this->hash2;
}