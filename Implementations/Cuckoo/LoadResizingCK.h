//
// Created by nnstein on 16/03/19.
//

#ifndef HASHTABLE_THESIS_LOADRESIZINGCK_H
#define HASHTABLE_THESIS_LOADRESIZINGCK_H


#include "BasicCuckoo.h"

using namespace std;

template<class K, class E>
class LoadResizingCK : public BasicCuckoo<K,E> {
    double loadPercent;
public:
    LoadResizingCK(unsigned numSlots, Hash<K>* hash1, Hash<K>* hash2);
    LoadResizingCK(unsigned numSlots, Hash<K>* hash1, Hash<K>* hash2, double loadPercent);
    int insert_element(K&, E&);
    int remove_element(K&);
};

#include "LoadResizingCK.tpp"


#endif //HASHTABLE_THESIS_LOADRESIZINGCK_H
