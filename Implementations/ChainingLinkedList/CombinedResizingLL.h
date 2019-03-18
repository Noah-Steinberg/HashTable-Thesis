//
// Created by nnstein on 16/03/19.
//

#ifndef HASHTABLE_THESIS_COMBINEDRESIZINGLL_H
#define HASHTABLE_THESIS_COMBINEDRESIZINGLL_H


#include "BasicChainingLinkedList.h"

using namespace std;

template<class K, class E>
class CombinedResizingLL : public BasicChainingLinkedList<K,E> {
    int maxChain;
    double loadPercent;
public:
    CombinedResizingLL(unsigned numSlots, Hash<K>* hash);
    CombinedResizingLL(unsigned numSlots, Hash<K>* hash, double loadPercent, int maxChain);
    int insert_element(K&, E&);
    int remove_element(K&);
    HashSlot<K,E>& get_slot(unsigned, K&, int&);
};

#include "CombinedResizingLL.tpp"


#endif //HASHTABLE_THESIS_COMBINEDRESIZINGLL_H
