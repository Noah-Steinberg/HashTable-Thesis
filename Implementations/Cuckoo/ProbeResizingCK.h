//
// Created by nnstein on 16/03/19.
//

#ifndef HASHTABLE_THESIS_PROBERESIZINGCK_H
#define HASHTABLE_THESIS_PROBERESIZINGCK_H


#include "BasicCuckoo.h"

using namespace std;

template<class K, class E>
class ProbeResizingCK : public BasicCuckoo<K,E> {
    int maxChain;
public:
    ProbeResizingCK(unsigned numSlots, Hash<K>* hash, Hash<K>* hash2);
    ProbeResizingCK(unsigned numSlots, Hash<K>* hash, Hash<K>* hash2, int maxChain);
    int insert_element(K&, E&);
};

#include "ProbeResizingCK.tpp"

#endif //HASHTABLE_THESIS_PROBERESIZINGCK_H
