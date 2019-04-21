//
// Created by nnstein on 20/10/18.
//

#ifndef HASHTABLE_THESIS_HASHFUNCTION_H
#define HASHTABLE_THESIS_HASHFUNCTION_H
#include <cstdlib>
#include <functional>

using namespace std;
template<class K>
class Hash{
    unsigned seed = 0;
    size_t digestSize = 0;

public:
    Hash() = default;

    Hash(unsigned seed, size_t digestSize){
        this->seed = seed;
        this->digestSize = digestSize;
    }
    virtual unsigned digest(K data){
        return (unsigned) std::hash<K>{}(data);
    }
};


#endif //HASHTABLE_THESIS_HASHFUNCTION_H
