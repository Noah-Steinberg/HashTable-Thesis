//
// Created by nnstein on 20/10/18.
//

#ifndef HASHTABLE_THESIS_HASHFUNCTION_H
#define HASHTABLE_THESIS_HASHFUNCTION_H


template<typename K>

class HashFunction{
    HashFunction() = default;
    virtual int generate_hash(K key) = 0;
};


#endif //HASHTABLE_THESIS_HASHFUNCTION_H
