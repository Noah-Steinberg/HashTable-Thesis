//
// Created by nnstein on 16/03/19.
//

#include "ProbeResizingLL.h"


template<class K, class E>
ProbeResizingLL<K,E>::ProbeResizingLL(unsigned numSlots, Hash<K> *hash)
: BasicChainingLinkedList<K,E>::BasicChainingLinkedList(numSlots, hash){
    this->maxChain = 32;
}

template<class K, class E>
ProbeResizingLL<K,E>::ProbeResizingLL(unsigned numSlots, Hash<K> *hash, int maxChain)
: BasicChainingLinkedList<K,E>::BasicChainingLinkedList(numSlots, hash){
    this->maxChain = maxChain;
}

template<class K, class E>
HashSlot<K,E>& ProbeResizingLL<K,E>::get_slot(unsigned hash, K& key, int& retcode)  {
    retcode = KEY_NOT_FOUND;
    hash = hash % this->numSlots;

    if(this->slots[hash].empty()){
        this->slots[hash].push_front(HashSlot<K,E>());
        return this->slots[hash].front();
    }
    else{
        int counter = 0;
        for (auto& ele: this->slots[hash]){
            if(ele.get_key()==key){
                retcode = KEY_ALREADY_EXISTS;
                return ele;
            }
            counter++;
            if(counter>=this->maxChain){
                this->resize();
                hash = this->hash->digest(key);
                return this->get_slot(hash, key, retcode);
            }
        }
        this->slots[hash].push_front(HashSlot<K,E>());
        return this->slots[hash].front();
    }
}