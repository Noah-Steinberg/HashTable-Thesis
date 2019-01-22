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
    int get_slot(unsigned hash, K&, shared_ptr<HashSlot<K,E>>&, bool);
public:
    BasicChainingBST(unsigned numSlots, Hash<K> hash);

};

#include "BasicChainingBST.tpp"
#endif //HASHTABLE_THESIS_CHAININGBST_H
