cmake_minimum_required(VERSION 3.6)   # CMake version check
project(HashTable-Thesis)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 11)            # Enable c++11 standard

set(SOURCE_FILES main.cpp Implementations/HashTable.tpp Implementations/HashTable.h HashFunctions/Hash.h Util/HashSlot.tpp Util/HashSlot.h Implementations/ChainingLinkedList/BasicChainingLinkedList.tpp Implementations/ChainingLinkedList/BasicChainingLinkedList.h Util/enums.h Util/BST.tpp Util/BST.h)            # Add main.cpp file of project root directory as source file
add_executable(exec ${SOURCE_FILES})       # Add executable target with source files listed in SOURCE_FILES variable