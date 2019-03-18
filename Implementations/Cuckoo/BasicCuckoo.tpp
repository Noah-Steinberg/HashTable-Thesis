//
// Created by nnstein on 05/02/19.
//

#include "BasicCuckoo.h"
#include <set>

template<class K, class E>
BasicCuckoo<K,E>::BasicCuckoo(unsigned numSlots, Hash<K>* hash1, Hash<K>* hash2) {
    this->hash1 = hash1;
    this->hash2 = hash2;
    this->slots1 = std::vector<CuckooHashSlot<K,E>>(numSlots);
    this->slots2 = std::vector<CuckooHashSlot<K,E>>(numSlots);
    this->numSlots = numSlots;
}

template<class K, class E>
CuckooHashSlot<K,E>& BasicCuckoo<K,E>::get_slot(unsigned hash1, unsigned hash2, K& key, int& retcode) {
    retcode = SUCCESS;
    unsigned slot1_i = hash1 % this->numSlots;
    unsigned slot2_i = hash2 % this->numSlots;

    if(this->slots1[slot1_i].is_empty() ||
            (!this->slots1[slot1_i].is_active() && this->slots1[slot1_i].get_key()==key)){
        retcode = KEY_NOT_FOUND;
        return this->slots1[slot1_i];
    }
    else if(this->slots1[slot1_i].get_key()==key){
        retcode = KEY_ALREADY_EXISTS;
        return this->slots1[slot1_i];
    }
    else if(this->slots2[slot2_i].is_empty() ||
       (!this->slots2[slot2_i].is_active() && this->slots2[slot2_i].get_key()==key)){
        retcode = KEY_NOT_FOUND;
        return this->slots2[slot2_i];
    }
    else if(this->slots2[slot2_i].get_key()==key){
        retcode = KEY_ALREADY_EXISTS;
        return this->slots2[slot2_i];
    }
    else{
        retcode = KEY_NOT_FOUND;
        return this->slots1[slot1_i];
    }
}

template<class K, class E>
int BasicCuckoo<K,E>::insert_element(K &key, E &element, bool update){
    int retval = SUCCESS;
    unsigned hash1 = this->hash1->digest(key);
    unsigned hash2 = this->hash2->digest(key);
    CuckooHashSlot<K,E> newSlot = CuckooHashSlot<K,E>(hash1, hash2, key, element);
    unsigned i = hash1 % this->numSlots;
    unsigned i2 = hash2 % this->numSlots;
    CuckooHashSlot<K,E> tmpSlot;
    bool swapFirst = true;

    if(this->slots1[i].get_key()==key || this->slots2[i2].get_key()==key){
        return KEY_ALREADY_EXISTS;
    }

    while(true){
        if(this->slots1[i].is_empty()){
            this->slots1[i] = newSlot;
            break;
        }
        else if(this->slots2[i2].is_empty()){
            this->slots2[i2] = newSlot;
            break;
        }
        else{
            if(swapFirst){
                tmpSlot = this->slots1[i];
                this->slots1[i] = newSlot;
                newSlot = tmpSlot;
                i = newSlot.get_hash() % this->numSlots;
                i2 = newSlot.get_hash2() % this->numSlots;
                swapFirst = false;
            }
            else{
                tmpSlot = this->slots2[i2];
                this->slots2[i2] = newSlot;
                newSlot = tmpSlot;
                i = newSlot.get_hash() % this->numSlots;
                i2 = newSlot.get_hash2() % this->numSlots;
                swapFirst = true;
            }
        }
    }

    return retval;
}


template<class K, class E>
int BasicCuckoo<K,E>::get_element(K &key, E &element){
    int retval = 0;
    unsigned hash1 = this->hash1->digest(key);
    unsigned hash2 = this->hash2->digest(key);
    CuckooHashSlot<K,E>& slot = this->get_slot(hash1, hash2, key, retval);
    if( slot.is_active()) {
        element = slot.get_element();
    }
    retval  = retval==KEY_ALREADY_EXISTS ? SUCCESS : retval;
    return retval;
}


template<class K, class E>
int BasicCuckoo<K,E>::remove_element(K &key){
    int retval = 0;
    unsigned hash1 = this->hash1->digest(key);
    unsigned hash2 = this->hash2->digest(key);
    CuckooHashSlot<K,E>& slot = this->get_slot(hash1, hash2, key, retval);
    if(retval != KEY_NOT_FOUND){
        /*
         * Sets key and element to null
         * By default, this means hash tables are tombstone baseed
         * Some tables will need to override depending on implementation
         * Some tables will need to have a dedicated remove_slot to handle logic
         */
        retval=SUCCESS;
        slot.toggle_active();
    }
    return retval;
}

template<class K, class E>
int BasicCuckoo<K,E>::resize() {
    this->numSlots += this->numSlots;

    std::vector<CuckooHashSlot<K,E>> oldSlots1 = this->slots1;
    this->slots1 = std::vector<CuckooHashSlot<K,E>>(this->numSlots);

    std::vector<CuckooHashSlot<K,E>> oldSlots2 = this->slots2;
    this->slots2 = std::vector<CuckooHashSlot<K,E>>(this->numSlots);

    HashSlot<K,E> curr;
    this->numElements = 0;

    for(auto iterator1=oldSlots1.begin(); iterator1<oldSlots1.end(); iterator1++){
        curr = *iterator1;
        if(!curr.is_empty() || curr.is_active()){
            K key = curr.get_key();
            E element = curr.get_element();
            this->insert_element(key, element);
        }
    }

    for(auto iterator1=oldSlots2.begin(); iterator1<oldSlots2.end(); iterator1++){
        curr = *iterator1;
        if(!curr.is_empty() || curr.is_active()){
            K key = curr.get_key();
            E element = curr.get_element();
            this->insert_element(key, element);
        }
    }
    return SUCCESS;
}