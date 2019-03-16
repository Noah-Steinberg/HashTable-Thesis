//
// Created by nnstein on 20/10/18.
//

#include "BasicChainingBST.h"
using namespace std;

template<class K, class E>
BasicChainingBST<K,E>::BasicChainingBST(unsigned numSlots, Hash<K>* hash) {
    this->numSlots = numSlots;
    this->hash = hash;
    this->slots = vector<BSTTree<K,E>>(numSlots);
}

template<class K, class E>
HashSlot<K,E>& BasicChainingBST<K,E>::get_slot(unsigned hash, K &key, int& retcode){

    hash = hash % this->numSlots;

    HashSlot<K,E>& slot = this->slots[hash].get(key, retcode);

    return slot;
}

template<class K, class E>
int BasicChainingBST<K,E>::insert_element(K& key, E& element){
    int retcode = SUCCESS;
    unsigned hash = this->hash->digest(key) % this->numSlots;
    HashSlot<K,E> newSlot = HashSlot<K,E>(hash, key, element);
    HashSlot<K,E>& oldSlot = this->get_slot(hash, key, retcode);

    if(retcode==SUCCESS){
        retcode=KEY_ALREADY_EXISTS;
    }
    else if(retcode==KEY_NOT_FOUND){
        this->slots[hash].insert(newSlot);
        return SUCCESS;
    }
    return retcode;
}

template<class K, class E>
int BasicChainingBST<K,E>::resize(){
    vector<BSTTree<K,E>> oldSlots = this->slots;
    this->slots = vector<BSTTree<K,E>>(this->numSlots*2);

    HashSlot<K,E> curr;

    for(auto iterator1=oldSlots.begin(); iterator1<oldSlots.end(); iterator1++){
        BSTIterator<K,E> iterator2 = BSTIterator<K,E>((*iterator1).get_root());
        while(iterator2.hasNext()){
            curr = iterator2.next();
            if(!curr.is_empty() || curr.is_active()){
                K key = curr.get_key();
                E element = curr.get_element();
                this->insert_element(key, element);
            }
        }
    }
    return SUCCESS;
}