//
// Created by nnstein on 16/03/19.
//

#ifndef HASHTABLE_THESIS_COMBINEDRESIZINGCK_H
#define HASHTABLE_THESIS_COMBINEDRESIZINGCK_H


#include "BasicCuckoo.h"

using namespace std;

template<class K, class E>
class CombinedResizingCK : public BasicCuckoo<K,E> {
    int maxChain;
    double loadPercent;
public:
    CombinedResizingCK(unsigned numSlots, Hash<K>* hash, Hash<K>* hash2);
    CombinedResizingCK(unsigned numSlots, Hash<K>* hash, Hash<K>* hash2, double loadPercent, int maxChain);
    int insert_element(K&, E&);
    int remove_element(K&);
};

#include "CombinedResizingCK.tpp"


#endif //HASHTABLE_THESIS_COMBINEDRESIZINGCK_H
