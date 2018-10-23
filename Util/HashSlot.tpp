//
// Created by nnstein on 20/10/18.
//

template<class K, class E>
HashSlot<K,E>::HashSlot(unsigned int hash, K key, E element) {
    this->hash = hash;
    this->key = key;
    this->element = element;
}

template<class K, class E>
int HashSlot<K,E>::get_hash() {
    return this->hash;
}

template<class K, class E>
K HashSlot<K,E>::get_key() {
    return this->key;
}

template<class K, class E>
E HashSlot<K,E>::get_element() {
    return this->element;
}

template<class K, class E>
void HashSlot<K,E>::set_hash(unsigned int hash ) {
    this->hash = hash;
}

template<class K, class E>
void HashSlot<K,E>::set_key(K key) {
    this->key = key;
}

template<class K, class E>
void HashSlot<K,E>::set_element(E element) {
    this->element = element;
}