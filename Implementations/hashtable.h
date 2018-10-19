#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "hashslot.h"
#include "hashfunction.h"
template<typename K, typename E>

class HashTable
{
    HashSlot**  slots;
    int         numSlots;
    HashFunction<K> get_hash;
    virtual int find_slot(K key, HashSlot* slotReturn) = 0;
    
    public:
        int get_element(K key, E* element);
        int insert_element(K key, E element, bool update);
        int remove_element(K key, E* element);
};

#endif