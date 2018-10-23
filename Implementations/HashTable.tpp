//
// Created by nnstein on 20/10/18.
//

#include "HashTable.h"

HashTable::HashTable(unsigned int numSlots, HashFunction<K> get_hash) {
    this->numSlots = numSlots;
    this->get_hash = get_hash;
    this->slots = malloc(sizeof(HashSlot) * numSlots);
}


template<class K, class E>
int HashTable::get_element(K key, E *element) {
    int retval = 0;
    HashSlot<K,E>* slot = NULL;

    retval = this->find_slot(key, slot, NULL);
    element = slot->get_element();
    return retval
}

template<class K, class E>
int HashTable::insert_element(K key, E element, bool update) {
    int retval = 0;
    unsigned int hash;
    HashSlot<K,E>* slot = NULL;

    retval = this->find_slot(key, slot, NULL, true);
    if(retval == KEY_NOT_FOUND){
        hash = this->get_hash(key);
        slot->set_hash(hash);
        slot->set_key(key);
        slot->set_element(element);
    }
    return retval
}

template<class K, class E>
int HashTable::remove_element(K key, E *element) {
    int retval = 0;
    unsigned int hash;
    HashSlot<K,E>* slot = NULL;

    retval = this->find_slot(key, slot, NULL, true);
    if(retval != KEY_NOT_FOUND){
        /*
         * Sets key and element to null
         * By default, this means hash tables are tombstone baseed
         * Some tables will need to override depending on implementation
         * Some tables will need to have a dedicated remove_slot to handle logic
         */
        hash = this->get_hash(key);
        slot->set_hash(hash);
        slot->set_key(NULL);
        slot->set_element(NULL);
    }
    return retval
}
