//
// Created by nnstein on 20/10/18.
//


template<class K, class E>
HashSlot<K,E>::HashSlot(unsigned hash, const K key, const E element) {
    this->hash = hash;
    this->key = key;
    this->element = element;
    this->active = true;
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
bool HashSlot<K,E>::get_active() const {
    return this->active;
}

template<class K, class E>
void HashSlot<K,E>::set_hash(unsigned hash ) {
    this->hash = hash;
}

template<class K, class E>
void HashSlot<K,E>::set_key(const K key) {
    this->key = key;
}

template<class K, class E>
void HashSlot<K,E>::set_element(const E element) {
    this->element = element;
}

template<class K,class E>
void HashSlot<K,E>::toggle_active() {
    this->active = !this->active;
}