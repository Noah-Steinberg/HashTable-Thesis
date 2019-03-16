//
// Created by nnstein on 20/10/18.
//

#ifndef HASHTABLE_THESIS_BASICROBINHOOD_H
#define HASHTABLE_THESIS_BASICROBINHOOD_H

#include "../../Util/enums.h"
#include "../HashTable.h"
#include <vector>
#include <forward_list>
#include <memory>

template<class K, class E>
class BasicRobinHood : public HashTable<K,E> {
protected:
    std::vector<HashSlot<K,E>>  slots;
    HashSlot<K,E>& get_slot(unsigned, K&, int&);
    int resize();
public:
    BasicRobinHood(unsigned numSlots, Hash<K>* hash);
    int insert_element(K&, E&, bool update=false);

};

#include "BasicRobinHood.tpp"
#endif //HASHTABLE_THESIS_BASICROBINHOOD_H
