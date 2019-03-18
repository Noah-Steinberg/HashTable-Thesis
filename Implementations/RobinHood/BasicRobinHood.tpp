//
// Created by nnstein on 20/10/18.
//

#include "BasicRobinHood.h"

template<class K, class E>
BasicRobinHood<K,E>::BasicRobinHood(unsigned numSlots, Hash<K>* hash) {
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
            retcode = KEY_ALREADY_EXISTS;
            break;
        }
        else{
            tar_counter = index - (this->slots[index].get_hash() % this->numSlots);
            tar_counter = tar_counter < 0 ? tar_counter+this->numSlots : tar_counter;
            if(curr_counter>tar_counter){
                    retcode =  KEY_NOT_FOUND;
                    break;
            }
        }
        ++curr_counter;
        index = (index + 1) % this->numSlots;
    }
    return this->slots[index];
}


template<class K, class E>
int BasicRobinHood<K,E>::insert_element(K &key, E &element, bool update){
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

    while(true){
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
    return retcode;
}

template<class K, class E>
int BasicRobinHood<K,E>::resize() {
    std::vector<HashSlot<K,E>> oldSlots = this->slots;
    this->numSlots += this->numSlots;
    this->slots = std::vector<HashSlot<K,E>>(this->numSlots);

    HashSlot<K,E> curr;

    this->numElements = 0;
    for(auto iterator1=oldSlots.begin(); iterator1<oldSlots.end(); iterator1++){
        curr = *iterator1;
        if(!curr.is_empty() || curr.is_active()){
            K key = curr.get_key();
            E element = curr.get_element();
            this->insert_element(key, element);
        }
    }
    return SUCCESS;
}
