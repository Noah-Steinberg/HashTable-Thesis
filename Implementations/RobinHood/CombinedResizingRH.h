//
// Created by nnstein on 16/03/19.
//

#ifndef HASHTABLE_THESIS_COMBINEDRESIZINGRH_H
#define HASHTABLE_THESIS_COMBINEDRESIZINGRH_H


#include "BasicRobinHood.h"

using namespace std;

template<class K, class E>
class CombinedResizingRH : public BasicRobinHood<K,E> {
    int maxChain;
    double loadPercent;
public:
    CombinedResizingRH(unsigned numSlots, Hash<K>* hash);
    CombinedResizingRH(unsigned numSlots, Hash<K>* hash, double loadPercent, int maxChain);
    int insert_element(K&, E&);
    int remove_element(K&);
};

#include "CombinedResizingRH.tpp"


#endif //HASHTABLE_THESIS_COMBINEDRESIZINGRH_H
