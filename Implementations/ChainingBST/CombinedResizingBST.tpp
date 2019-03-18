//
// Created by nnstein on 16/03/19.
//

#include "CombinedResizingBST.h"

template<class K, class E>
CombinedResizingBST<K,E>::CombinedResizingBST(unsigned numSlots, Hash<K> *hash)
: BasicChainingBST<K,E>::BasicChainingBST(numSlots, hash){
    this->loadPercent = 0.9;
    this->maxChain = 32;
    this->numElements = 0;
}

template<class K, class E>
CombinedResizingBST<K,E>::CombinedResizingBST(unsigned numSlots, Hash<K> *hash, double loadPercent, int maxChain)
: BasicChainingBST<K,E>::BasicChainingBST(numSlots, hash){
    this->loadPercent = loadPercent;
    this->maxChain = maxChain;
    this->numElements = 0;
}

template<class K, class E>
int CombinedResizingBST<K,E>::insert_element(K& key, E& element) {
    int retcode = BasicChainingBST<K,E>::insert_element(key, element);
    if(retcode==SUCCESS){
        unsigned hash = this->hash->digest(key);
        hash = hash % this->numSlots;
        this->numElements++;
        if(this->numElements>=(int) (this->loadPercent*this->numSlots)){
            this->resize();
        }
        else if(this->slots[hash].numElements>=32){
            this->resize();
        }
    }
    return retcode;
}
template<class K, class E>
int CombinedResizingBST<K,E>::remove_element(K& key) {
    int retcode = HashTable<K,E>::remove_element(key);
    if (retcode == SUCCESS) {
        this->numElements--;
    }
    return retcode;
}