#ifndef HASHSLOT_H
#define HASHSLOT_H

template<typename K, typename E>
class HashSlot
{
    int hash;
    K key;
    E element;

    public:
        HashSlot(int hash, K key, E element)
            {this->hash = hash; this->key = key; this->element = element;}
        int get_hash(){ return this->hash; }
        K   get_key(){ return this->key; }
        E   get_element(){ return this->element; }
};
#endif