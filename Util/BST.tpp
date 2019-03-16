//
// Created by nnstein on 19/01/19.
//



#include "BST.h"
using namespace std;

template<class K, class E>
BSTTree<K,E>::BSTTree(const BSTTree<K,E>& base){
    HashSlot<K,E> tmp;
    HashSlot<K,E> curr;
    BSTIterator<K,E> it = BSTIterator<K,E>(base.root.get());
    while(it.hasNext()){
        tmp = it.next();
        curr = HashSlot<K,E>(tmp);
        this->insert(curr);
    }
}

template<class K, class E>
int BSTTree<K,E>::insert(HashSlot<K,E>& newSlot)
{
    unique_ptr<BSTNode<K,E>> newNode = make_unique<BSTNode<K,E>>(newSlot);
    if(!this->root)
    {
        this->root = move(newNode);
        return 0;
    }
    BSTNode<K,E>* cur = this->root.get();
    while(cur != nullptr)
    {
        if(newNode->get_val() < cur->get_val())
        {
            if(cur->get_left() == nullptr)
            {
                cur->left = move(newNode);
                return 0;
            }
            else
            {
                cur = cur->get_left();
            }
        }

        else if(newNode->get_val() > cur->get_val() )
        {
            if(cur->get_right() == nullptr)
            {
                cur->right = move(newNode);
                return 0;
            }
            else
            {
                cur = cur->get_right();
            }
        }
        else if (newNode->get_val()==cur->get_val())
        {
            if(!newNode->get_data().is_active())
            {
                newNode->get_data().toggle_active();
                return 0;
            }
            else
            {
                 return KEY_ALREADY_EXISTS;
            }
        }
    }
    return UNDEFINED_FAILURE;

}

template<class K, class E>
int BSTTree<K,E>::remove(K key)
{
    BSTNode<K,E>* cur = this->root.get();
    BSTNode<K,E>* parent = nullptr;
    int exists = 0;
    bool leftChild = false;
    while(cur != nullptr)
    {
        if(key < cur->get_val())
        {
            parent = cur;
            cur = cur->get_left();
            leftChild = true;
        }

        else if(key > cur->get_val() )
        {
            parent = cur;
            cur = cur->get_right();
            leftChild = false;
        }
        else if(cur->get_data().is_active()){
            exists = 1;
            break;
        }
    }
    if(exists)
    {
        if(this->deleteItems)
        {
            if(cur->get_right()==nullptr && cur->get_left()==nullptr)
            {
                if(parent==nullptr){
                    this->root.reset();
                }
                else if(leftChild){
                    parent->left.reset();
                }
                else{
                    parent->right.reset();
                }
            }
            else if(cur->get_right()!=nullptr && cur->get_left()!=nullptr)
            {
                this->replace_inorder_predecessor(cur, parent);
            }
            else
            {
                if(cur->get_right()==nullptr)
                {
                    parent->left = move(cur->left);
                }
                else
                {
                    parent->right = move(cur->right);
                }
            }
        }
        else
        {
            cur->get_data().toggle_active();
        }
        return 0;

    }
    else
    {
        return -1;
    }
}

template<class K, class E>
void BSTTree<K,E>::replace_inorder_predecessor(BSTNode<K,E>* cur, BSTNode<K,E>* parent)
{
    cur = cur->get_right();
    while(cur->get_left()!=nullptr)
    {
        cur = cur->get_left();
    }
    parent->data = move(cur->data);
}

template<class K, class E>
HashSlot<K,E>& BSTTree<K,E>::get(K key, int& retcode)
{
    retcode = KEY_NOT_FOUND;
    BSTNode<K,E>* cur = this->root.get();
    while(cur != nullptr) {
        if (key < cur->get_val()) {
            cur = cur->get_left();
        } else if (key > cur->get_val()) {
            cur = cur->get_right();
        } else {
            if (cur->get_data().is_active()) {
                retcode = SUCCESS;
                return cur->get_data();
            }
            break;

        }
    }
    return this->default_slot;
}