//
// Created by nnstein on 16/03/19.
//

#ifndef HASHTABLE_THESIS_PROBERESIZINGBST_H
#define HASHTABLE_THESIS_PROBERESIZINGBST_H


#include "BasicChainingBST.h"

using namespace std;

template<class K, class E>
class ProbeResizingBST : public BasicChainingBST<K,E> {
    int maxChain;
public:
    ProbeResizingBST(unsigned numSlots, Hash<K>* hash);
    ProbeResizingBST(unsigned numSlots, Hash<K>* hash, int maxChain);
    int insert_element(K&, E&);
};

#include "ProbeResizingBST.tpp"


#endif //HASHTABLE_THESIS_PROBERESIZINGBST_H
