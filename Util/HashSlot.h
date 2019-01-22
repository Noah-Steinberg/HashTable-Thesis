//
// Created by nnstein on 20/10/18.
//

#ifndef HASHTABLE_THESIS_HASHSLOT_H
#define HASHTABLE_THESIS_HASHSLOT_H
#include <memory>


template<class K, class E>
class HashSlot {
    unsigned hash;
    K key;
    E element;
    bool active;

public:
    HashSlot(unsigned hash, const K key, const E element);
    HashSlot() = default;
    unsigned get_hash() const;
    K  get_key() const;
    E  get_element() const;
    bool get_active() const;
    void set_hash(unsigned hash);
    void set_key(const K key);
    void set_element(const E element);
    void toggle_active();
};

#include "HashSlot.tpp"
#endif //HASHTABLE_THESIS_HASHSLOT_H
