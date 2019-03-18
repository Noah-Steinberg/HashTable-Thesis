//
// Created by nnstein on 16/03/19.
//

#ifndef HASHTABLE_THESIS_LOADRESIZINGLL_H
#define HASHTABLE_THESIS_LOADRESIZINGLL_H


#include "BasicChainingLinkedList.h"

using namespace std;

template<class K, class E>
class LoadResizingLL : public BasicChainingLinkedList<K,E> {
    double loadPercent;
public:
    LoadResizingLL(unsigned numSlots, Hash<K>* hash);
    LoadResizingLL(unsigned numSlots, Hash<K>* hash, double loadPercent);
    int insert_element(K&, E&);
    int remove_element(K&);
};

#include "LoadResizingLL.tpp"


#endif //HASHTABLE_THESIS_LOADRESIZINGLL_H
