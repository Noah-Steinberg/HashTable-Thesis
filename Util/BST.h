//
// Created by nnstein on 19/01/19.
//

#ifndef HASHTABLE_THESIS_BST_H
#define HASHTABLE_THESIS_BST_H

#include "../Util/enums.h"
#include "HashSlot.h"
#include <vector>
#include <forward_list>
#include <memory>
#include <iostream>

using namespace std;

template<class K, class E>
class BSTNode {

public:
    unique_ptr<HashSlot<K,E>> data;
    unique_ptr<BSTNode<K,E>> left;
    unique_ptr<BSTNode<K,E>> right;

    explicit BSTNode(HashSlot<K,E> newSlot){
        this->data = move(make_unique<HashSlot<K,E>>(newSlot));
        this->left = nullptr;
        this->right = nullptr;
    }

    BSTNode<K,E>* get_left(){
        return this->left.get();
    }
    BSTNode<K,E>* get_right(){
        return this->right.get();
    }
    HashSlot<K,E>& get_data(){
        return *this->data;
    }
    K get_val(){
        return this->data->get_key();
    }

};


template<class K, class E>
class BSTTree{
private:
    void replace_inorder_predecessor(BSTNode<K,E>*, BSTNode<K,E>*);
    bool deleteItems = false;
protected:
    unique_ptr<BSTNode<K,E>> root = nullptr;
public:
    BSTTree() = default;
    explicit BSTTree(bool deleteItems){
        this->deleteItems = deleteItems;
    }
    int insert(HashSlot<K,E>&);
    int remove(K key);
    int get(K key, HashSlot<K,E>&);
};
#include "BST.tpp"
#endif //HASHTABLE_THESIS_BST_H
