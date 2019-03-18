//
// Created by nnstein on 20/10/18.
//

#ifndef HASHTABLE_THESIS_CHAININGBST_H
#define HASHTABLE_THESIS_CHAININGBST_H

#include "../../Util/enums.h"
#include "../../Util/BST.h"
#include "../HashTable.h"
#include <vector>
#include <forward_list>
#include <memory>

using namespace std;

template<class K, class E>
class BasicChainingBST : public HashTable<K,E> {
protected:
    vector<BSTTree<K,E>>  slots;
    HashSlot<K,E>& get_slot(unsigned hash, K&, int&);
    int resize();
public:
    BasicChainingBST(unsigned numSlots, Hash<K>* hash);

    virtual int insert_element(K&, E&);

};

#include "BasicChainingBST.tpp"
#endif //HASHTABLE_THESIS_CHAININGBST_H
