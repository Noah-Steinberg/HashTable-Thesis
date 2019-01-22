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
    shared_ptr<HashSlot<K,E>> data;
    shared_ptr<BSTNode<K,E>> left;
    shared_ptr<BSTNode<K,E>> right;
    bool deleted;

public:
    explicit BSTNode(shared_ptr<HashSlot<K,E>> data){
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
        this->deleted = false;
    }

    void set_left(shared_ptr<BSTNode<K, E>> left){
        this->left.swap(left);
    }
    void set_right(shared_ptr<BSTNode<K, E>> right){
        this->right.swap(right);
    }
    void mark_deleted(){
        this->deleted=true;
    }

    shared_ptr<BSTNode<K,E>> get_left(){
        return this->left;
    }
    shared_ptr<BSTNode<K,E>> get_right(){
        return this->right;
    }
    shared_ptr<HashSlot<K,E>> get_data(){
        return this->data;
    }
    K get_val(){
        return this->data->get_element();
    }
    bool is_deleted(){
        return this->deleted;
    }


};


template<class K, class E>
class BSTTree{
private:
    void replace_inorder_predecessor(shared_ptr<BSTNode<K,E>>&);
protected:
    shared_ptr<BSTNode<K,E>> root = nullptr;
public:
    BSTTree() = default;
    int insert(shared_ptr<HashSlot<K,E>>);
    int remove(K key);
    int get(K key, shared_ptr<HashSlot<K,E>>&);
    int mark_deleted(K key);
};
#include "BST.tpp"
#endif //HASHTABLE_THESIS_BST_H
