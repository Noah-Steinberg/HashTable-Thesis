//
// Created by nnstein on 16/03/19.
//

#include "LoadResizingCK.h"

template<class K, class E>
LoadResizingCK<K,E>::LoadResizingCK(unsigned numSlots, Hash<K>* hash1, Hash<K>* hash2)
: BasicCuckoo<K,E>::BasicCuckoo(numSlots, hash1, hash2){
    this->loadPercent = 0.9;
    this->numElements = 0;
}

template<class K, class E>
LoadResizingCK<K,E>::LoadResizingCK(unsigned numSlots, Hash<K>* hash1, Hash<K>* hash2, double loadPercent)
: BasicCuckoo<K,E>::BasicCuckoo(numSlots, hash1, hash2){
    this->loadPercent = loadPercent;
    this->numElements = 0;
}
template<class K, class E>
int LoadResizingCK<K,E>::insert_element(K &key, E &element){
    insertElement:
    int retval = SUCCESS;
    unsigned hash1 = this->hash1->digest(key);
    unsigned hash2 = this->hash2->digest(key);
    CuckooHashSlot<K,E> newSlot = CuckooHashSlot<K,E>(hash1, hash2, key, element);
    unsigned i = hash1 % this->numSlots;
    unsigned i2 = hash2 % this->numSlots;
    CuckooHashSlot<K,E> tmpSlot;
    bool swapFirst = true;
    bool resizeFlag = false;

    if(this->slots1[i].get_key()==key || this->slots2[i2].get_key()==key){
        return KEY_ALREADY_EXISTS;
    }

    this->numElements++;
    if(this->numElements>=(int) (this->loadPercent*this->numSlots)){
        resizeFlag = true;
        for(int j=0; j<this->numSlots;j++){
            if(this->slots1[j].is_empty()){
                this->slots1[j] = newSlot;
                break;
            }
            else if(this->slots2[j].is_empty()){
                this->slots2[j] = newSlot;
                break;
            }
        }
    }

    while(!resizeFlag){
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
    if(resizeFlag){
        this->resize();
    }

    return retval;
}
template<class K, class E>
int LoadResizingCK<K,E>::remove_element(K& key) {
    int retcode = BasicCuckoo<K,E>::remove_element(key);
    if (retcode == SUCCESS) {
        this->numElements--;
    }
    return retcode;
}
