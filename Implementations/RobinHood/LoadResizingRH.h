//
// Created by nnstein on 16/03/19.
//

#ifndef HASHTABLE_THESIS_LOADRESIZINGRH_H
#define HASHTABLE_THESIS_LOADRESIZINGRH_H


#include "BasicRobinHood.h"

using namespace std;

template<class K, class E>
class LoadResizingRH : public BasicRobinHood<K,E> {
    double loadPercent;
public:
    LoadResizingRH(unsigned numSlots, Hash<K>* hash);
    LoadResizingRH(unsigned numSlots, Hash<K>* hash, double loadPercent);
    int insert_element(K&, E&);
    int remove_element(K&);
};

#include "LoadResizingRH.tpp"


#endif //HASHTABLE_THESIS_LOADRESIZINGRH_H
