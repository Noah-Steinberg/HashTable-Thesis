//
// Created by nnstein on 20/10/18.
//

#include "BasicChainingLinkedList.h"

template<class K, class E>
BasicChainingLinkedList<K,E>::BasicChainingLinkedList(unsigned numSlots, Hash<K>* hash) {
    this->numSlots = numSlots;
    this->hash = hash;
    this->slots = std::vector<std::forward_list<HashSlot<K,E>>>(numSlots);
}

template<class K, class E>
HashSlot<K,E>& BasicChainingLinkedList<K,E>::get_slot(unsigned hash, K& key, int& retcode)  {
    retcode = KEY_NOT_FOUND;
    hash = hash % this->numSlots;

    if(this->slots[hash].empty()){
        this->slots[hash].push_front(HashSlot<K,E>());
        return this->slots[hash].front();
    }
    else{
        for (auto& ele: this->slots[hash]){
            if(ele.get_key()==key){
                retcode = KEY_ALREADY_EXISTS;
                return ele;
            }
        }
        this->slots[hash].push_front(HashSlot<K,E>());
        return this->slots[hash].front();
    }

}

template<class K, class E>
int BasicChainingLinkedList<K,E>::resize() {
    std::vector<std::forward_list<HashSlot<K,E>>> oldSlots = this->slots;
    this->slots = std::vector<std::forward_list<HashSlot<K,E>>>(this->numSlots*2);

    HashSlot<K,E> curr;

    for(auto iterator1=oldSlots.begin(); iterator1<oldSlots.end(); iterator1++){
        for(auto iterator2=((*iterator1).begin()); iterator2!=((*iterator1).end()); iterator2++){
            curr = *iterator2;
            if(!curr.is_empty() || curr.is_active()){
                K key = curr.get_key();
                E element = curr.get_element();
                this->insert_element(key, element);
            }
        }
    }
    return SUCCESS;
}


