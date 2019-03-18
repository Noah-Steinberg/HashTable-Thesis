//
// Created by nnstein on 13/02/19.
//


#include <fstream>
#include <iterator>
#include <iostream>

#include "../Util/enums.h"

#include "../Implementations/ChainingLinkedList/BasicChainingLinkedList.h"
#include "../Implementations/ChainingBST/BasicChainingBST.h"
#include "../Implementations/RobinHood/BasicRobinHood.h"
#include "../Implementations/Cuckoo/BasicCuckoo.h"

#include "../HashFunctions/FNV1a.h"

#include "catch.hpp"
#include "../Util/TestStatistic.h"
#include "../Util/TestResults.h"
#include "../Util/MemorySize.h"

using namespace std;
TEST_CASE("Memory Test", "[memory]") {
    unsigned total_insertions = 1000000;
    unsigned key;
    unsigned element;
    FNV1a<unsigned> hash_function = FNV1a<unsigned>();
    hash_function.seed = 1234567890;

    ifstream f("../TestData/random.txt");
    istream_iterator<unsigned> start(f), end;
    vector<unsigned> numbers(start, end);

    std::string test_name;
    std::vector<TestStatistic> statistics = std::vector<TestStatistic>();
    TestStatistic memory_size = TestStatistic("Max Memory Usage", "KiloBytes");
    TestStatistic init_memory_size = TestStatistic("Initial Memory Usage", "KiloBytes");
    TestStatistic base_memory_size = TestStatistic("Initial Memory Usage", "KiloBytes");
    init_memory_size.set_value((double) getMemory());


    SECTION("Chained_LL_Table_Test"){
        test_name = "LL_BASIC";


        auto table = BasicChainingLinkedList<unsigned,unsigned>(total_insertions, &hash_function);
        base_memory_size.set_value((double) getMemory());
        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            retcode = table.insert_element(key, element);
            REQUIRE(retcode==SUCCESS);
        }


        INFO("Checking for all elements")
        for(int i=0; i<total_insertions;++i){
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode==SUCCESS);
            REQUIRE(element==ele);
        }

        memory_size.set_value((double) getMemory());

    }
    SECTION("Chained_BST_Table_Test") {
        test_name = "BST_BASIC";

        auto table = BasicChainingBST<unsigned, unsigned>(total_insertions, &hash_function);
        base_memory_size.set_value((double) getMemory());

        INFO("Inserting all elements")
        for (int i = 0; i < total_insertions; ++i) {

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            retcode = table.insert_element(key, element);
            REQUIRE(retcode == SUCCESS);
        }


        INFO("Checking for all elements")
        for (int i = 0; i < total_insertions; ++i) {
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode == SUCCESS);
            REQUIRE(element == ele);
        }

        memory_size.set_value((double) getMemory());
    }

    SECTION("Robin_Hood_Hash_Table_Test"){
        test_name = "RH_BASIC";

        auto table = BasicRobinHood<unsigned,unsigned>(total_insertions*2, &hash_function);
        base_memory_size.set_value((double) getMemory());

        base_memory_size.set_value((double) getMemory());

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            retcode = table.insert_element(key, element);
            REQUIRE(retcode==SUCCESS);
        }


        INFO("Checking for all elements")
        for(int i=0; i<total_insertions;++i){
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode==SUCCESS);
            REQUIRE(element==ele);
        }

        memory_size.set_value((double) getMemory());
    }

    SECTION("Cuckoo_Table_Test"){
        test_name = "CK_BASIC";

        Hash<unsigned> hash_function2 = Hash<unsigned>();
        auto table = BasicCuckoo<unsigned,unsigned>(total_insertions, &hash_function, &hash_function2);
        base_memory_size.set_value((double) getMemory());

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            retcode = table.insert_element(key, element);
            REQUIRE(retcode==SUCCESS);
        }


        INFO("Checking for all elements")
        for(int i=0; i<total_insertions;++i){
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode==SUCCESS);
            REQUIRE(element==ele);
        }

        memory_size.set_value((double) getMemory());
    }

    statistics.push_back(init_memory_size);
    statistics.push_back(base_memory_size);
    statistics.push_back(memory_size);

    TestResults output = TestResults(test_name, statistics);
    output.write_results();

}