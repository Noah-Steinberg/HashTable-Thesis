//
// Created by nnstein on 16/03/19.
//

#include "ProbeResizingBST.h"

template<class K, class E>
ProbeResizingBST<K,E>::ProbeResizingBST(unsigned numSlots, Hash<K> *hash)
: BasicChainingBST<K,E>::BasicChainingBST(numSlots, hash){
    this->maxChain = 32;
}

template<class K, class E>
ProbeResizingBST<K,E>::ProbeResizingBST(unsigned numSlots, Hash<K> *hash, int maxChain)
: BasicChainingBST<K,E>::BasicChainingBST(numSlots, hash){
    this->maxChain = maxChain;
}

template<class K, class E>
int ProbeResizingBST<K,E>::insert_element(K& key, E& element) {
    int retcode = BasicChainingBST<K,E>::insert_element(key, element);
    if(retcode==SUCCESS){
        unsigned hash = this->hash->digest(key);
        hash = hash % this->numSlots;
        if(this->slots[hash].numElements>=32){
            this->resize();
        }
    }
    return retcode;
}