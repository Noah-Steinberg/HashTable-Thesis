//
// Created by nnstein on 20/10/18.
//

#include "HashTable.h"
template<class K, class E>
HashTable<K,E>::HashTable(unsigned numSlots, Hash* hash) {
    this->numSlots = numSlots;
    this->hash = hash;
    this->slots = new HashSlot<K,E> *[numSlots];
}

template<class K, class E>
HashTable<K,E>::~HashTable(){
    free(this->slots);
}

template<class K, class E>
int HashTable<K,E>::get_element(K* key, E **element) {
    int retval = 0;
    unsigned hash;
    auto slot = new HashSlot<K,E>();
    hash = this->hash->digest((void*) key);
    retval = this->get_slot(hash, key, slot, nullptr, true);
    if(slot->get_element()==nullptr){
        *element=nullptr;
    }
    else{
        *element = slot->get_element();
    }
    return retval;
}

template<class K, class E>
int HashTable<K,E>::insert_element(K* key, E* element, bool update) {
    int retval = 0;
    unsigned hash;
    auto slot = new HashSlot<K,E>();
    hash = this->hash->digest((void*) key);
    retval = this->get_slot(hash, key, slot, nullptr, true);

    if(retval == KEY_NOT_FOUND || (retval==0 && update)){
        slot->set_hash(hash);
        slot->set_key(key);
        slot->set_element(element);
    }
    return retval;
}

template<class K, class E>
int HashTable<K,E>::remove_element(K* key, E** element) {
    int retval = 0;
    unsigned hash;
    auto slot = new HashSlot<K,E>();
    hash = this->hash->digest((void*) &key);

    retval = this->get_slot(hash, key, slot, nullptr, true);
    if(retval != KEY_NOT_FOUND){
        /*
         * Sets key and element to null
         * By default, this means hash tables are tombstone baseed
         * Some tables will need to override depending on implementation
         * Some tables will need to have a dedicated remove_slot to handle logic
         */
        hash = this->hash->digest((void*) key);
        slot->set_hash(hash);
        slot->set_key(nullptr);
        slot->set_element(nullptr);
    }
    return retval;
}
