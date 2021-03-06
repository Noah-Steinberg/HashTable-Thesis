//
// Created by nnstein on 20/10/18.
//
using namespace std;
#include "HashTable.h"
template<class K, class E>
HashTable<K,E>::HashTable(unsigned numSlots, Hash<K>* hash) {
    this->numSlots = numSlots;
    this->hash = hash;
    this->slots = std::vector<HashSlot<K,E>>(10);
}

template<class K, class E>
int HashTable<K,E>::get_element(K &key, E &element){
    int retval = SUCCESS;
    unsigned hash;
    hash = this->hash->digest(key);
    HashSlot<K,E>& slot = this->get_slot(hash, key, retval);
    if( slot.is_active()) {
        retval = retval==KEY_ALREADY_EXISTS ? SUCCESS : retval;
        element = slot.get_element();
    }
    else{
        retval = KEY_NOT_FOUND;
    }
    return retval;
}

template<class K, class E>
int HashTable<K,E>::insert_element(K &key, E &element, bool update){
    int retval = 0;
    unsigned hash;
    hash = this->hash->digest(key);
    HashSlot<K,E>& slot = this->get_slot(hash, key, retval);
    slot = HashSlot<K,E>(hash, key, element);
    retval = retval==KEY_NOT_FOUND ? SUCCESS : retval;
    return retval;
}

template<class K, class E>
int HashTable<K,E>::remove_element(K &key){
    int retval = SUCCESS;
    unsigned hash;
    hash = this->hash->digest(key);

    HashSlot<K,E>& slot = this->get_slot(hash, key, retval);
    if(retval != KEY_NOT_FOUND){
        /*
         * Sets key and element to null
         * By default, this means hash tables are tombstone baseed
         * Some tables will need to override depending on implementation
         * Some tables will need to have a dedicated remove_slot to handle logic
         */
        retval = SUCCESS;
        slot.toggle_active();
    }
    return retval;
}