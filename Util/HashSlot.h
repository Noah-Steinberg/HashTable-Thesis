//
// Created by nnstein on 20/10/18.
//

#ifndef HASHTABLE_THESIS_HASHSLOT_H
#define HASHTABLE_THESIS_HASHSLOT_H
#include <memory>
using namespace std;

template<class K, class E>
class HashSlot {
protected:
    unsigned hash;
    K key;
    E element;
    bool active;
    bool empty = true;

public:
    HashSlot(unsigned, K, E);
    HashSlot(const HashSlot<K,E>&);
    HashSlot() = default;
    unsigned get_hash() const;
    K  get_key() const;
    E  get_element() const;
    bool is_active() const;
    bool is_empty() const;
    void toggle_active();
};

#include "HashSlot.tpp"
#endif //HASHTABLE_THESIS_HASHSLOT_H
