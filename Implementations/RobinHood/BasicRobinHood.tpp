//
// Created by nnstein on 20/10/18.
//

#include "BasicRobinHood.h"

template<class K, class E>
BasicRobinHood<K,E>::BasicRobinHood(unsigned numSlots, Hash<K> hash) {
    this->numSlots = numSlots;
    this->hash = hash;
    this->slots = std::vector<HashSlot<K,E>>(numSlots);
}

template<class K, class E>
HashSlot<K,E>& BasicRobinHood<K,E>::get_slot(unsigned hash, K& key, int& retcode)  {

    int index = hash % this->numSlots;
    int curr_counter = 0;
    int tar_counter = 0;
    retcode = KEY_NOT_FOUND;
    while(!this->slots[index].is_empty()){
        if(this->slots[index].get_key()==key && this->slots[index].is_active()){
            retcode = SUCCESS;
            break;
        }
        else{
            tar_counter = index - (this->slots[index].get_hash() % this->numSlots);
            if(curr_counter>tar_counter){
                    retcode =  KEY_NOT_FOUND;
                    break;
            }
        }
        ++curr_counter;
        ++index;
    }
    return this->slots[index];
}


template<class K, class E>
int BasicRobinHood<K,E>::insert_element(K &key, E &element, bool update){
    int retcode = SUCCESS;
    unsigned hash = this->hash.digest(key);
    int index = hash % this->numSlots;
    int curr_counter = 0;
    int tar_counter = 0;
    HashSlot<K,E> newSlot = HashSlot<K,E>(hash, key, element);
    HashSlot<K,E>& currSlot = this->slots[index];

    while(true){
        if(currSlot.get_key()==key && currSlot.is_active()){
            retcode = KEY_ALREADY_EXISTS;
            break;
        }
        else if(currSlot.is_empty()){
            currSlot = newSlot;
            retcode = SUCCESS;
            break;
        }
        else{
            tar_counter = index - (currSlot.get_hash() % this->numSlots);
            if(curr_counter>tar_counter){
                HashSlot<K,E> tmpSlot = currSlot;
                currSlot = newSlot;
                newSlot = tmpSlot;
                curr_counter = 0;
            }
        }
        ++curr_counter;
        index = (index + 1) % this->numSlots;
        currSlot = this->slots[index];
    }
    return retcode;
}