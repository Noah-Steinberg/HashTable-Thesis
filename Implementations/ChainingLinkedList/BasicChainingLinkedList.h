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
class BasicChainingLinkedList : public HashTable<K,E> {
protected:
    std::vector<std::forward_list<HashSlot<K,E>>>  slots;
    int get_slot(unsigned, K&, HashSlot<K,E>&, bool);
public:
    BasicChainingLinkedList(unsigned numSlots, Hash<K> hash);

};

#include "BasicChainingLinkedList.tpp"
#endif //HASHTABLE_THESIS_CHAININGLINKEDLIST_H
