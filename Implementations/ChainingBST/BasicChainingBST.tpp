//
// Created by nnstein on 20/10/18.
//

#include "BasicChainingBST.h"
using namespace std;

template<class K, class E>
BasicChainingBST<K,E>::BasicChainingBST(unsigned numSlots, Hash<K> hash) {
    this->numSlots = numSlots;
    this->hash = hash;
    this->slots = vector<BSTTree<K,E>>(numSlots);
}

template<class K, class E>
int BasicChainingBST<K,E>::get_slot(unsigned hash, K &key, shared_ptr<HashSlot<K,E>> &slotReturn, bool createSlot) {

    hash = hash % this->numSlots;

    int ret = this->slots[hash].get(key, slotReturn);

    if(createSlot && ret==0){
        return KEY_ALREADY_EXISTS;
    }
    else if(createSlot && ret==KEY_NOT_FOUND){
        this->slots[hash].insert(slotReturn);
    }
    return ret;

}