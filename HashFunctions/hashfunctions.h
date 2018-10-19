#ifndef HASHFUNCTION_H
#define HASHFUNCTION_H
template<typename K>

class HashFunction{
    HashFunction() {};
    virtual int generate_hash(K key) = 0;
};

//https://github.com/okdshin/PicoSHA2
class SHA2 : class HashFunction{

};

//http://www.zedwood.com/article/cpp-md5-function
class MD5 : class HashFunction{

};

//https://github.com/whitfin/siphash-cpp/tree/master/src
class SIPHash: class HashFunction{

};

//https://create.stephan-brumme.com/fnv-hash/
class FNV1a: class HashFunction{

};
#endif