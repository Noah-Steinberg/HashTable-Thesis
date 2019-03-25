//
// Created by nnstein on 16/03/19.
//

#include "CombinedResizingLL.h"

template<class K, class E>
CombinedResizingLL<K,E>::CombinedResizingLL(unsigned numSlots, Hash<K> *hash)
: BasicChainingLinkedList<K,E>::BasicChainingLinkedList(numSlots, hash){
    this->loadPercent = 0.9;
    this->maxChain = 32;
    this->numElements = 0;
}

template<class K, class E>
CombinedResizingLL<K,E>::CombinedResizingLL(unsigned numSlots, Hash<K> *hash, double loadPercent, int maxChain)
: BasicChainingLinkedList<K,E>::BasicChainingLinkedList(numSlots, hash){
    this->loadPercent = loadPercent;
    this->maxChain = maxChain;
    this->numElements = 0;
}

template<class K, class E>
int CombinedResizingLL<K,E>::insert_element(K& key, E& element) {
    int retcode = BasicChainingLinkedList<K,E>::insert_element(key, element);
    if(retcode==SUCCESS){
        this->numElements++;
        if(this->numElements>=(int) (this->loadPercent*this->numSlots)){
            this->resize();
        }
    }
    return retcode;
}
template<class K, class E>
int CombinedResizingLL<K,E>::remove_element(K& key) {
    int retcode = HashTable<K,E>::remove_element(key);
    if (retcode == SUCCESS) {
        this->numElements--;
    }
    return retcode;
}

template<class K, class E>
HashSlot<K,E>& CombinedResizingLL<K,E>::get_slot(unsigned hash, K& key, int& retcode)  {
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



