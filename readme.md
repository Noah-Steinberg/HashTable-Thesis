# Hash Tables
This project is an implementation of various hash table techniques with various customizations. 
Overall this project has a focus on comparing many different techniques, rather than perfect implementation.
This means some sacrifices were made in order to improve the customization of the hash tables. 
However, each hash table should be affected equally by the changes, minimizing any unfairness.

### Environment
Build in CLion by IntelliJ using CMAKE

### Dependencies:
#### catch2:
Catch2 stands for C++ Automated Test Cases in a Header and is a multi-paradigm test framework for C++. which also supports Objective-C (and maybe C). It is primarily distributed as a single header file, although certain extensions may require additional headers.
https://github.com/catchorg/Catch2

Used for unit testing/profiling of table time complexity and memory usage.

#### sparsehash:
sparsehash is a hash table implementation created by google.
https://github.com/sparsehash/sparsehash 

Used for comparison purposes to created tables.


### Refences:
MD5 algorithm from: http://www.zedwood.com/article/cpp-md5-function

SHA2 algorithm from: http://www.zedwood.com/article/cpp-sha256-function

FNV1A implementation based on: https://create.stephan-brumme.com/fnv-hash/

Memory Profiling from: https://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process

