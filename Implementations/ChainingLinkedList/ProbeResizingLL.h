//
// Created by nnstein on 16/03/19.
//

#ifndef HASHTABLE_THESIS_PROBERESIZINGLL_H
#define HASHTABLE_THESIS_PROBERESIZINGLL_H


#include "BasicChainingLinkedList.h"

using namespace std;

template<class K, class E>
class ProbeResizingLL : public BasicChainingLinkedList<K,E> {
    int numElements;
    int maxChain;

public:
    ProbeResizingLL(unsigned numSlots, Hash<K>* hash);
    ProbeResizingLL(unsigned numSlots, Hash<K>* hash, int maxChain);
    HashSlot<K,E>& get_slot(unsigned, K&, int&);
};

#include "ProbeResizingLL.tpp"


#endif //HASHTABLE_THESIS_PROBERESIZINGLL_H
