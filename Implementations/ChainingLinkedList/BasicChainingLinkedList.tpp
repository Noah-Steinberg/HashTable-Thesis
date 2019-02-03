//
// Created by nnstein on 20/10/18.
//

#include "BasicChainingLinkedList.h"

template<class K, class E>
BasicChainingLinkedList<K,E>::BasicChainingLinkedList(unsigned numSlots, Hash<K> hash) {
    this->numSlots = numSlots;
    this->hash = hash;
    this->slots = std::vector<std::forward_list<HashSlot<K,E>>>(numSlots);
}

template<class K, class E>
int BasicChainingLinkedList<K,E>::get_slot(unsigned hash, K& key, HashSlot<K,E>& slotReturn, bool createSlot)  {

    hash = hash % this->numSlots;

    for (auto const& ele: this->slots[hash]){
        if(ele.get_key()==key){
            if(createSlot){
                return KEY_ALREADY_EXISTS;
            }
            slotReturn = ele;
            return SUCCESS;
        }
    }

    if(createSlot){
        this->slots[hash].push_front(slotReturn);
    }
    return KEY_NOT_FOUND;

}