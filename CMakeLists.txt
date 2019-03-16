cmake_minimum_required(VERSION 3.6)   # CMake version check
project(HashTable-Thesis)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

set(SOURCE_FILES Tests/main.cpp Implementations/HashTable.tpp Implementations/HashTable.h HashFunctions/Hash.h Util/HashSlot.tpp Util/HashSlot.h Implementations/ChainingLinkedList/BasicChainingLinkedList.tpp Implementations/ChainingLinkedList/BasicChainingLinkedList.h Util/enums.h Util/BST.tpp Util/BST.h Implementations/Cuckoo/BasicCuckoo.tpp Implementations/Cuckoo/BasicCuckoo.h Util/CuckooHashSlot.tpp Util/CuckooHashSlot.h Tests/basic_test.cpp HashFunctions/FNV1a.h Util/TestTimer.h Util/TestResults.h Tests/resize_test.cpp)            # Add main.cpp file of project root directory as source file
add_executable(exec ${SOURCE_FILES})       # Add executable target with source files listed in SOURCE_FILES variable