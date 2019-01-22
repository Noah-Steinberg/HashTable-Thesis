//
// Created by nnstein on 20/10/18.
//

#ifndef HASHTABLE_THESIS_CHAININGLINKEDLIST_H
#define HASHTABLE_THESIS_CHAININGLINKEDLIST_H

#include "../../Util/enums.h"
#include "../HashTable.h"
#include <vector>
#include <forward_list>
#include <memory>

template<class K, class E>
class ChainingLinkedList : public HashTable<K,E> {
protected:
    std::vector<std::map<HashSlot<K,E>>>  slots;
    int get_slot(unsigned hash, const K &key, HashSlot<K,E> &slotReturn,
            std::unique_ptr<int> index=nullptr, bool createSlot=false);
public:
    ChainingLinkedList(unsigned numSlots, Hash<K> hash);

};

#include "../ChainingLinkedList/BasicChainingLinkedList.tpp"
#endif //HASHTABLE_THESIS_CHAININGLINKEDLIST_H
