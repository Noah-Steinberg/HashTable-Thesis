//
// Created by nnstein on 16/03/19.
//

#include "LoadResizingRH.h"

template<class K, class E>
LoadResizingRH<K,E>::LoadResizingRH(unsigned numSlots, Hash<K> *hash)
: BasicRobinHood<K,E>::BasicRobinHood(numSlots, hash){
    this->loadPercent = 0.9;
    this->numElements = 0;
}

template<class K, class E>
LoadResizingRH<K,E>::LoadResizingRH(unsigned numSlots, Hash<K> *hash, double loadPercent)
: BasicRobinHood<K,E>::BasicRobinHood(numSlots, hash){
    this->loadPercent = loadPercent;
    this->numElements = 0;
}
template<class K, class E>
int LoadResizingRH<K,E>::insert_element(K &key, E &element){
    insertElement:
    int retcode;
    unsigned hash = this->hash->digest(key);
    int index = hash % this->numSlots;
    int curr_counter = 0;
    int tar_counter = 0;
    HashSlot<K,E> newSlot = HashSlot<K,E>(hash, key, element);
    HashSlot<K,E> currSlot;

    this->get_slot(hash, key, retcode);
    if(retcode==KEY_ALREADY_EXISTS){
        return retcode;
    }

    this->numElements++;
    if(this->numElements>=(int) (this->loadPercent*this->numSlots)){
        this->resize();
        goto insertElement;
    }

    while(true){
        currSlot = this->slots[index];
        if(currSlot.get_key()==key && currSlot.is_active()){
            retcode = KEY_ALREADY_EXISTS;
            this->numElements--;
            break;
        }
        else if(currSlot.is_empty()){
            this->slots[index] = newSlot;
            retcode = SUCCESS;
            break;
        }
        else{
            tar_counter = index - (currSlot.get_hash() % this->numSlots);
            if(curr_counter>tar_counter){
                HashSlot<K,E> tmpSlot = currSlot;
                this->slots[index] = newSlot;
                newSlot = tmpSlot;
                curr_counter = tar_counter;
            }
        }
        ++curr_counter;
        index = (index + 1) % this->numSlots;
    }
    return retcode;
}
template<class K, class E>
int LoadResizingRH<K,E>::remove_element(K& key) {
    int retcode = BasicRobinHood<K,E>::remove_element(key);
    if (retcode == SUCCESS) {
        this->numElements--;
    }
    return retcode;
}
