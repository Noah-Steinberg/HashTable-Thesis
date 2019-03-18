//
// Created by nnstein on 16/03/19.
//

#include "ProbeResizingRH.h"

template<class K, class E>
ProbeResizingRH<K,E>::ProbeResizingRH(unsigned numSlots, Hash<K> *hash)
: BasicRobinHood<K,E>::BasicRobinHood(numSlots, hash){
    this->maxChain = 32;
}

template<class K, class E>
ProbeResizingRH<K,E>::ProbeResizingRH(unsigned numSlots, Hash<K> *hash, int maxChain)
: BasicRobinHood<K,E>::BasicRobinHood(numSlots, hash){
    this->maxChain = maxChain;
}
template<class K, class E>
int ProbeResizingRH<K,E>::insert_element(K &key, E &element){
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

    int counter=0;
    while(true){
        counter++;
        if(counter>=this->maxChain){
            resizeFlag = true;
        }
        currSlot = this->slots[index];
        if(currSlot.get_key()==key && currSlot.is_active()){
            retcode = KEY_ALREADY_EXISTS;
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