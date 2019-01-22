//
// Created by nnstein on 20/10/18.
//

#include "BasicChainingLinkedList.h"

template<class K, class E>
ChainingLinkedList<K,E>::ChainingLinkedList(unsigned numSlots, Hash<K> hash) {
    this->numSlots = numSlots;
    this->hash = hash;
    this->slots = std::vector<std::forward_list<HashSlot<K,E>>>(numSlots);
}

template<class K, class E>
int ChainingLinkedList<K,E>::get_slot(unsigned hash, const K &key, HashSlot<K,E> &slotReturn,
        std::unique_ptr<int> index, bool createSlot) {

    hash = hash % this->numSlots;

    for (auto const& ele: this->slots[hash]){
        if(ele.get_key()==key){
            if(createSlot){
                return KEY_ALREADY_EXISTS;
            }
            slotReturn = ele;
            return 0;
        }
    }

    if(createSlot){
        this->slots[hash].push_front(slotReturn);
    }
    return KEY_NOT_FOUND;

}