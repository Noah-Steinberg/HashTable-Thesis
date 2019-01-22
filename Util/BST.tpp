//
// Created by nnstein on 19/01/19.
//



#include "BST.h"
using namespace std;

template<class K, class E>
int BSTTree<K,E>::insert(shared_ptr<HashSlot<K,E>> newSlot)
{
    shared_ptr<BSTNode<K,E>> newNode = make_shared<BSTNode<K,E>>(newSlot);
    if(this->root == nullptr)
    {
        this->root = newNode;
        return 0;
    }
    shared_ptr<BSTNode<K,E>> subRoot = this->root;
    while(subRoot != nullptr && !subRoot->is_deleted())
    {
        if(newNode->get_val() < subRoot->get_val())
        {
            if(subRoot->get_left() == nullptr || subRoot->get_left()->is_deleted())
            {
                subRoot->set_left(newNode);
                return 0;
            }
            else
            {
                subRoot = subRoot->get_left();
            }
        }

        else if(newNode->get_val() > subRoot->get_val() )
        {
            if(subRoot->get_right() == nullptr || subRoot->get_right()->is_deleted())
            {
                subRoot->set_right(newNode);
                return 0;
            }
            else
            {
                subRoot = subRoot->get_right();
            }
        }
    }
    return -1;

}

template<class K, class E>
int BSTTree<K,E>::remove(K key)
{
    shared_ptr<BSTNode<K,E>> node = this->root;
    shared_ptr<BSTNode<K,E>> parent;
    int exists = 0;
    while(node != nullptr)
    {
        if(key < node->get_val())
        {
            parent = node;
            node = node->get_left();
        }

        else if(key > node->get_val() )
        {
            parent = node;
            node = node->get_right();
        }
        else if(!node->is_deleted()){
            exists = 1;
            break;
        }
    }
    if(exists)
    {
        if(node->get_right()==nullptr && node->get_left()==nullptr)
        {
            node->mark_deleted();
        }
        else if(node->get_right()!=nullptr && node->get_left()!=nullptr)
        {
            this->replace_inorder_predecessor(node);
        }
        else
        {
            if(node->get_right()==nullptr)
            {
                *node = *node->get_left();
            }
            else
            {
                *node = *node->get_right();
            }
        }
        return 0;

    }
    else
    {
        return -1;
    }
}

template<class K, class E>
void BSTTree<K,E>::replace_inorder_predecessor(shared_ptr<BSTNode<K,E>>& subRoot)
{
    shared_ptr<BSTNode<K,E>> rightTree = subRoot->get_right();
    while(rightTree->get_left()!=nullptr)
    {
        rightTree = rightTree->get_left();
    }
    *subRoot->get_data() = *rightTree->get_data();
}

template<class K, class E>
int BSTTree<K,E>::get(K key, shared_ptr<HashSlot<K,E>> &slot)
{
    shared_ptr<BSTNode<K,E>> subRoot = this->root;
    while(subRoot != nullptr && !subRoot->is_deleted())
    {
        if(key < subRoot->get_val())
        {
            subRoot = subRoot->get_left();
        }

        else if(key > subRoot->get_val() )
        {
            subRoot = subRoot->get_right();
        }
        else if(!subRoot->is_deleted()){
            slot = subRoot->get_data();
            return 0;
        }
    }
    return -1;
}

template<class K, class E>
int BSTTree<K,E>::mark_deleted(K key)
{
    shared_ptr<BSTNode<K,E>> subRoot = this->root;
    while(subRoot != nullptr && !subRoot->is_deleted())
    {
        if(key < subRoot->get_val())
        {
            subRoot = subRoot->get_left();
        }

        else if(key > subRoot->get_val() )
        {
            subRoot = subRoot->get_right();
        }
        else
        {
            subRoot->mark_deleted();
            return 0;
        }
    }
    return -1;
}
