//
// Created by nnstein on 16/03/19.
//

#ifndef HASHTABLE_THESIS_LOADRESIZINGBST_H
#define HASHTABLE_THESIS_LOADRESIZINGBST_H

#include "BasicChainingBST.h"

using namespace std;

template<class K, class E>
class LoadResizingBST : public BasicChainingBST<K,E> {
    double loadPercent;
public:
    LoadResizingBST(unsigned numSlots, Hash<K>* hash);
    LoadResizingBST(unsigned numSlots, Hash<K>* hash, double loadPercent);
    int insert_element(K&, E&);
    int remove_element(K&);
};

#include "LoadResizingBST.tpp"


#endif //HASHTABLE_THESIS_LOADRESIZINGBST_H
