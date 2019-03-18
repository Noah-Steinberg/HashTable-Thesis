//
// Created by nnstein on 16/03/19.
//
#include "CombinedResizingRH.h"

template<class K, class E>
CombinedResizingRH<K,E>::CombinedResizingRH(unsigned numSlots, Hash<K> *hash)
: BasicRobinHood<K,E>::BasicRobinHood(numSlots, hash){
    this->loadPercent = 0.9;
    this->maxChain = 32;
    this->numElements = 0;
}

template<class K, class E>
CombinedResizingRH<K,E>::CombinedResizingRH(unsigned numSlots, Hash<K> *hash, double loadPercent, int maxChain)
: BasicRobinHood<K,E>::BasicRobinHood(numSlots, hash){
    this->loadPercent = loadPercent;
    this->maxChain = maxChain;
    this->numElements = 0;
}
template<class K, class E>
int CombinedResizingRH<K,E>::insert_element(K &key, E &element){
    int retcode;
    unsigned hash = this->hash->digest(key);
    int index = hash % this->numSlots;
    int curr_counter = 0;
    int tar_counter = 0;
    HashSlot<K,E> newSlot = HashSlot<K,E>(hash, key, element);
    HashSlot<K,E> currSlot;
    bool resizeFlag = false;

    this->get_slot(hash, key, retcode);
    if(retcode==KEY_ALREADY_EXISTS){
        return retcode;
    }

    this->numElements++;
    if(this->numElements>=(int) (this->loadPercent*this->numSlots)){
        resizeFlag = true;
    }

    int counter=0;
    while(true){
        counter++;
        if(counter>=this->maxChain){
            resizeFlag = true;
        }
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
    if(resizeFlag){
        this->resize();
    }
    return retcode;
}
template<class K, class E>
int CombinedResizingRH<K,E>::remove_element(K& key) {
    int retcode = BasicRobinHood<K,E>::remove_element(key);
    if (retcode == SUCCESS) {
        this->numElements--;
    }
    return retcode;
}
