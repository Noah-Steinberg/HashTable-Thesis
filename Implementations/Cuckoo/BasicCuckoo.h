//
// Created by nnstein on 05/02/19.
//

#ifndef HASHTABLE_THESIS_BASICCUCKOO_H
#define HASHTABLE_THESIS_BASICCUCKOO_H


#include "../../Util/enums.h"
#include "../HashTable.h"
#include "../../Util/CuckooHashSlot.h"
#include <vector>
#include <forward_list>
#include <memory>

template<class K, class E>
class BasicCuckoo {
protected:
    Hash<K>* hash1;
    Hash<K>* hash2;
    int numSlots;
    int numElements;
    int resizeFactor = 5;
    std::vector<CuckooHashSlot<K,E>>  slots1;
    std::vector<CuckooHashSlot<K,E>>  slots2;
    CuckooHashSlot<K,E>& get_slot(unsigned, unsigned, K&, int&);
    int resize();

public:
    BasicCuckoo(unsigned, Hash<K>*, Hash<K>*);
    int insert_element(K&, E&, bool update=false);
    int get_element(K& key, E& element);

    virtual int remove_element(K& key);
};

#include "BasicCuckoo.tpp"
#endif //HASHTABLE_THESIS_BASICCUCKOO_H
