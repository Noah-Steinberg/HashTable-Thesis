//
// Created by nnstein on 16/03/19.
//

#include "LoadResizingBST.h"

template<class K, class E>
LoadResizingBST<K,E>::LoadResizingBST(unsigned numSlots, Hash<K> *hash)
: BasicChainingBST<K,E>::BasicChainingBST(numSlots, hash){
    this->loadPercent = 0.9;
    this->numElements = 0;
}

template<class K, class E>
LoadResizingBST<K,E>::LoadResizingBST(unsigned numSlots, Hash<K> *hash, double loadPercent)
: BasicChainingBST<K,E>::BasicChainingBST(numSlots, hash){
    this->loadPercent = loadPercent;
    this->numElements = 0;
}

template<class K, class E>
int LoadResizingBST<K,E>::insert_element(K& key, E& element) {
    int retcode = BasicChainingBST<K,E>::insert_element(key, element);
    if(retcode==SUCCESS){
        unsigned hash = this->hash->digest(key);
        this->numElements++;
        if(this->numElements>=(int) (this->loadPercent*this->numSlots)){
            this->resize();
        }
    }
    return retcode;
}
template<class K, class E>
int LoadResizingBST<K,E>::remove_element(K& key) {
    int retcode = HashTable<K,E>::remove_element(key);
    if (retcode == SUCCESS) {
        this->numElements--;
    }
    return retcode;
}
