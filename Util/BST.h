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
#include <stack>

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
class BSTIterator {
    std::stack<BSTNode<K,E>*> stack;
public:
    BSTIterator(BSTNode<K,E>* root) {
        this->stack = std::stack<BSTNode<K,E>*>();

        while(root!= nullptr){
            this->stack.push(root);
            root = root->get_left();
        }
    };
    bool hasNext(){
        return !stack.empty();
    };
    HashSlot<K,E> next(){
        BSTNode<K,E>* curr = this->stack.top();
        this->stack.pop();
        HashSlot<K,E> result = curr->get_data();
        if(curr->get_right()!=nullptr){
            curr = curr->get_right();
            while(curr!=nullptr){
                this->stack.push(curr);
                curr = curr->get_left();
            }
        }
        return result;
    }

};


template<class K, class E>
class BSTTree{
private:
    void replace_inorder_predecessor(BSTNode<K,E>*, BSTNode<K,E>*);
    bool deleteItems = false;
protected:
    unique_ptr<BSTNode<K,E>> root = unique_ptr<BSTNode<K,E>>(nullptr);
    HashSlot<K,E> default_slot = HashSlot<K,E>();
public:
    BSTTree() = default;
    BSTTree(const BSTTree<K,E>&);
    explicit BSTTree(bool deleteItems){
        this->deleteItems = deleteItems;
    };
    BSTNode<K,E>* get_root(){
        return this->root.get();
    };
    int insert(HashSlot<K,E>&);
    int remove(K key);
    HashSlot<K,E>& get(K key, int&);
};
#include "BST.tpp"
#endif //HASHTABLE_THESIS_BST_H
