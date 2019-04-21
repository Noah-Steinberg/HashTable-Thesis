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
    unsigned hash = this->hash->digest(key);
    HashSlot<K,E> newSlot = HashSlot<K,E>(hash, key, element);
    this->get_slot(hash, key, retcode);
    hash = hash % this->numSlots;

    if(retcode==SUCCESS){
        return KEY_ALREADY_EXISTS;
    }
    else if(retcode==KEY_NOT_FOUND){
        this->slots[hash].insert(newSlot);
        return SUCCESS;
    }
    return retcode;
}

template<class K, class E>
int BasicChainingBST<K,E>::resize(){
    vector<BSTTree<K,E>> oldSlots = vector<BSTTree<K,E>>(this->numSlots);;
    for(int i=0; i<this->numSlots;i++) {
        this->slots[i].moveTree(oldSlots[i]);
    }

    this->numSlots *= this->resizeFactor;
    this->slots = vector<BSTTree<K,E>>(this->numSlots);
    this->numElements = 0;

    HashSlot<K,E> curr;
    int counter1 =0;
    int counter2 =0;
    for(auto iterator1=oldSlots.begin(); iterator1<oldSlots.end(); iterator1++){
        counter1++;
        if((*iterator1).numElements==0){
            continue;
        }
        BSTIterator<K,E> iterator2 = BSTIterator<K,E>((*iterator1).get_root());
        while(iterator2.hasNext()){
            counter2++;
            curr = iterator2.next();
            if(!curr.is_empty() && curr.is_active()){
                K key = curr.get_key();
                E element = curr.get_element();
                this->insert_element(key, element);
            }
        }
    }
    return SUCCESS;
}