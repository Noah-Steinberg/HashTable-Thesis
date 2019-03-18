//
// Created by nnstein on 16/03/19.
//

#ifndef HASHTABLE_THESIS_PROBERESIZINGRH_H
#define HASHTABLE_THESIS_PROBERESIZINGRH_H

#include "BasicRobinHood.h"

using namespace std;

template<class K, class E>
class ProbeResizingRH : public BasicRobinHood<K,E> {
    int maxChain;
public:
    ProbeResizingRH(unsigned numSlots, Hash<K>* hash);
    ProbeResizingRH(unsigned numSlots, Hash<K>* hash, int maxChain);
    int insert_element(K&, E&);
};

#include "ProbeResizingRH.tpp"


#endif //HASHTABLE_THESIS_PROBERESIZINGRH_H
