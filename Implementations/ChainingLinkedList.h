//
// Created by nnstein on 20/10/18.
//

#ifndef HASHTABLE_THESIS_CHAININGLINKEDLIST_H
#define HASHTABLE_THESIS_CHAININGLINKEDLIST_H

#include "../Util/enums.h"
#include "HashTable.h"
#include "../Util/HashNode.h"

template<class K, class E>
class ChainingLinkedList : public HashTable<K,E> {
protected:
    ~ChainingLinkedList();
    HashNode<K,E>**  slots;
    int get_slot(unsigned hash, K* key, HashSlot<K,E>* slotReturn, int* index=nullptr, bool createSlot=false);
public:
    ChainingLinkedList(unsigned numSlots, Hash* hash);

};

#include "ChainingLinkedList.tpp"
#endif //HASHTABLE_THESIS_CHAININGLINKEDLIST_H
