//
// Created by nnstein on 16/03/19.
//

#include "ProbeResizingCK.h"

template<class K, class E>
ProbeResizingCK<K,E>::ProbeResizingCK(unsigned numSlots, Hash<K> *hash, Hash<K>* hash2)
: BasicCuckoo<K,E>::BasicCuckoo(numSlots, hash, hash2){
    this->maxChain = 32;
}

template<class K, class E>
ProbeResizingCK<K,E>::ProbeResizingCK(unsigned numSlots, Hash<K> *hash, Hash<K>* hash2, int maxChain)
: BasicCuckoo<K,E>::BasicCuckoo(numSlots, hash, hash2){
    this->maxChain = maxChain;
}

template<class K, class E>
int ProbeResizingCK<K,E>::insert_element(K &key, E &element){

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

    int counter=0;
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
        counter++;
        if(counter>=this->maxChain){
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
    }
    if(resizeFlag){
        this->resize();
    }

    return retval;
}
