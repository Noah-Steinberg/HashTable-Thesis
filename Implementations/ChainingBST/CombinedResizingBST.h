//
// Created by nnstein on 16/03/19.
//

#ifndef HASHTABLE_THESIS_COMBINEDRESIZINGBST_H
#define HASHTABLE_THESIS_COMBINEDRESIZINGBST_H

#include "BasicChainingBST.h"

using namespace std;

template<class K, class E>
class CombinedResizingBST : public BasicChainingBST<K,E> {
    int maxChain;
    double loadPercent;
public:
    CombinedResizingBST(unsigned numSlots, Hash<K>* hash);
    CombinedResizingBST(unsigned numSlots, Hash<K>* hash, double loadPercent, int maxChain);
    int insert_element(K&, E&);
    int remove_element(K&);
};

#include "CombinedResizingBST.tpp"

#endif //HASHTABLE_THESIS_COMBINEDRESIZINGBST_H
