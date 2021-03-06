//
// Created by nnstein on 20/10/18.
//


template<class K, class E>
HashSlot<K,E>::HashSlot(unsigned hash, K key, E element) {
    this->hash = hash;
    this->key = key;
    this->element = element;
    this->active = true;
    this->empty = false;
}

template<class K, class E>
HashSlot<K,E>::HashSlot(const HashSlot<K,E>& base) {
    this->hash = base.hash;
    this->key = base.key;
    this->element = base.element;
    this->active = base.active;
    this->empty = base.empty;
}

template<class K, class E>
unsigned HashSlot<K,E>::get_hash() const {
    return this->hash;
}

template<class K, class E>
K HashSlot<K,E>::get_key() const {
    return this->key;
}

template<class K, class E>
E HashSlot<K,E>::get_element() const {
    return this->element;
}

template<class K, class E>
bool HashSlot<K,E>::is_active() const {
    return this->active;
}

template<class K, class E>
bool HashSlot<K,E>::is_empty() const {
    return this->empty;
}

template<class K,class E>
void HashSlot<K,E>::toggle_active() {
    this->active = !this->active;
}