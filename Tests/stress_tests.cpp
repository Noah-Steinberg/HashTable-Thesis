//
// Created by nnstein on 20/03/19.
//
#include <fstream>
#include <iterator>
#include <iostream>

#include <sparsehash/sparse_hash_map>
#include <sparsehash/dense_hash_map>

#include "../Util/enums.h"

#include "../Implementations/ChainingLinkedList/CombinedResizingLL.h"
#include "../Implementations/ChainingBST/CombinedResizingBST.h"
#include "../Implementations/RobinHood/CombinedResizingRH.h"
#include "../Implementations/Cuckoo/CombinedResizingCK.h"

#include "../HashFunctions/FNV1a.h"

#include "catch.hpp"
#include "../Util/TestStatistic.h"
#include "../Util/TestResults.h"
#include "../Util/MemorySize.h"

using namespace std;
TEST_CASE("Insertion Stress Test", "[insert][stress]") {
    unsigned total_insertions = 40000000;
    unsigned key;
    unsigned element;
    FNV1a<unsigned> hash_function = FNV1a<unsigned>();
    hash_function.seed = 1234567890;

    ifstream f("../TestData/random_medium.txt");
    istream_iterator<unsigned> start(f), end;
    vector<unsigned> numbers(start, end);

    std::string test_name;
    std::vector<TestStatistic> statistics = std::vector<TestStatistic>();
    TestStatistic test_length = TestStatistic("Total Time", "Seconds");


    SECTION("LL"){
        test_name = "LL_INSERT_STRESS";

        test_length.start_timer();

        auto table = CombinedResizingLL<unsigned,unsigned>(1000, &hash_function);

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << i);
            retcode = table.insert_element(key, element);
            REQUIRE(retcode==SUCCESS);
        }


        test_length.stop_timer();
    }

    SECTION("BST"){
        test_name = "BST_INSERT_STRESS";

        test_length.start_timer();

        auto table = CombinedResizingBST<unsigned,unsigned>(1000, &hash_function);

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << i);
            retcode = table.insert_element(key, element);
            REQUIRE(retcode==SUCCESS);
        }


        test_length.stop_timer();
    }

    SECTION("RH"){
        test_name = "RH_INSERT_STRESS";

        test_length.start_timer();

        auto table = CombinedResizingRH<unsigned,unsigned>(1000, &hash_function);

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << i);
            retcode = table.insert_element(key, element);
            REQUIRE(retcode==SUCCESS);
        }


        test_length.stop_timer();
    }
    SECTION("CK"){
        test_name = "CK_INSERT_STRESS";

        test_length.start_timer();
        FNV1a<unsigned> hash_function2 = FNV1a<unsigned>();
        hash_function2.seed = 2345678901;
        auto table = CombinedResizingCK<unsigned,unsigned>(1000, &hash_function, &hash_function2);

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << i);
            retcode = table.insert_element(key, element);
            REQUIRE(retcode==SUCCESS);
        }


        test_length.stop_timer();
    }

    SECTION("sparse_hash_map"){
        test_name = "sparse_hash_map_INSERT_STRESS";

        test_length.start_timer();
        auto table = google::sparse_hash_map<unsigned,unsigned>(1000);
        table.set_deleted_key(0);

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){
            key = numbers[i];
            element = numbers[i];
            table[key] = element;
        }


        test_length.stop_timer();
    }

    SECTION("dense_hash_map"){
        test_name = "dense_hash_map_INSERT_STRESS";

        test_length.start_timer();
        auto table = google::dense_hash_map<unsigned,unsigned>(1000);
        table.set_empty_key(0);
        table.set_deleted_key(1);

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){
            key = numbers[i];
            element = numbers[i];
            table[key] = element;
        }


        test_length.stop_timer();
    }


    statistics.push_back(test_length);


    TestResults output = TestResults(test_name, statistics);
    output.write_results();

}

TEST_CASE("Retrieval Stress Test", "[retrieval][stress]") {
    unsigned total_insertions = 1000000;
    unsigned key;
    unsigned element;
    FNV1a<unsigned> hash_function = FNV1a<unsigned>();
    hash_function.seed = 1234567890;

    ifstream f("../TestData/random_medium.txt");
    istream_iterator<unsigned> start(f), end;
    vector<unsigned> numbers(start, end);

    std::string test_name;
    std::vector<TestStatistic> statistics = std::vector<TestStatistic>();
    TestStatistic test_length = TestStatistic("Total Time", "Seconds");


    SECTION("LL"){
        test_name = "LL_RETRIEVAL_STRESS";
        auto table = CombinedResizingLL<unsigned,unsigned>(total_insertions, &hash_function);

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << i);
            retcode = table.insert_element(key, element);
            REQUIRE(retcode==SUCCESS);
        }

        test_length.start_timer();
        INFO("Retrieval elements")
        for(int i=0; i<total_insertions*100
                ;++i){
            int j = i % total_insertions;
            int retcode;
            unsigned ele;
            key = numbers[j];
            element = numbers[j];
            INFO("Retrieving element " << j);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode==SUCCESS);
        }
        test_length.stop_timer();
    }

    SECTION("BST"){
        test_name = "BST_RETRIEVAL_STRESS";

        auto table = CombinedResizingBST<unsigned,unsigned>(total_insertions, &hash_function);

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){
            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << i);
            retcode = table.insert_element(key, element);
            REQUIRE(retcode==SUCCESS);
        }

        test_length.start_timer();
        INFO("Retrieval elements")
        for(int i=0; i<total_insertions*100;++i){
            int j = i % total_insertions;
            int retcode;
            unsigned ele;
            key = numbers[j];
            element = numbers[j];
            INFO("Retrieving element " << j);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode==SUCCESS);
        }
        test_length.stop_timer();
    }

    SECTION("RH"){
        test_name = "RH_RETRIEVAL_STRESS";

        auto table = CombinedResizingRH<unsigned,unsigned>(total_insertions, &hash_function);

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << i);
            retcode = table.insert_element(key, element);
            REQUIRE(retcode==SUCCESS);
        }

        test_length.start_timer();
        INFO("Retrieval elements")
        for(int i=0; i<total_insertions*100;++i){
            int j = i % total_insertions;
            int retcode;
            unsigned ele;
            key = numbers[j];
            element = numbers[j];
            INFO("Retrieving element " << j);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode==SUCCESS);
        }
        test_length.stop_timer();
    }
    SECTION("CK"){
        test_name = "CK_RETRIEVAL_STRESS";
        FNV1a<unsigned> hash_function2 = FNV1a<unsigned>();
        hash_function.seed = 2345678901;

        auto table = CombinedResizingCK<unsigned,unsigned>(total_insertions, &hash_function, &hash_function2);

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << i);
            retcode = table.insert_element(key, element);
            REQUIRE(retcode==SUCCESS);
        }

        test_length.start_timer();
        INFO("Retrieval elements")
        for(int i=0; i<total_insertions*100;++i){
            int j = i % total_insertions;
            int retcode;
            unsigned ele;
            key = numbers[j];
            element = numbers[j];
            INFO("Retrieving element " << j);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode==SUCCESS);
        }
        test_length.stop_timer();
    }

    SECTION("sparse_hash_map"){
        test_name = "sparse_hash_map_retrieval_STRESS";

        test_length.start_timer();
        auto table = google::sparse_hash_map<unsigned,unsigned>(total_insertions);
        table.set_deleted_key(0);

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){
            key = numbers[i];
            element = numbers[i];
            table[key] = element;
        }

        test_length.start_timer();
        INFO("Retrieval elements")
        for(int i=0; i<total_insertions*100;++i){
            int j = i % total_insertions;
            int retcode;
            unsigned ele;
            key = numbers[j];
            element = numbers[j];
            INFO("Retrieving element " << j);
            ele = table[key];
            REQUIRE(element==ele);
        }
        test_length.stop_timer();
    }

    SECTION("dense_hash_map"){
        test_name = "dense_hash_map_retrieval_STRESS";

        test_length.start_timer();
        auto table = google::dense_hash_map<unsigned,unsigned>(total_insertions);
        table.set_empty_key(0);
        table.set_deleted_key(1);

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){
            key = numbers[i];
            element = numbers[i];
            table[key] = element;
        }

        test_length.start_timer();
        INFO("Retrieval elements")
        for(int i=0; i<total_insertions*100;++i){
            int j = i % total_insertions;
            int retcode;
            unsigned ele;
            key = numbers[j];
            element = numbers[j];
            INFO("Retrieving element " << j);
            ele = table[key];
            REQUIRE(element==ele);
        }
        test_length.stop_timer();
    }


    statistics.push_back(test_length);


    TestResults output = TestResults(test_name, statistics);
    output.write_results();

}

TEST_CASE("Removal Stress Test", "[removal][stress]") {
    unsigned total_insertions = 1000000;
    unsigned removal_amount = 500000;
    unsigned key;
    unsigned element;
    FNV1a<unsigned> hash_function = FNV1a<unsigned>();
    hash_function.seed = 1234567890;

    ifstream f("../TestData/random_medium.txt");
    istream_iterator<unsigned> start(f), end;
    vector<unsigned> numbers(start, end);

    std::string test_name;
    std::vector<TestStatistic> statistics = std::vector<TestStatistic>();
    TestStatistic test_length = TestStatistic("Total Time", "Seconds");


    SECTION("LL"){
        test_name = "LL_REMOVAL_STRESS";
        auto table = CombinedResizingLL<unsigned,unsigned>(total_insertions, &hash_function);

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << i);
            retcode = table.insert_element(key, element);
            REQUIRE(retcode==SUCCESS);
        }
        test_length.start_timer();
        INFO("Performing repeated insertion and removal")
        for(int i=0; i<20;i++){
            for(int j=total_insertions+(removal_amount*i);j<total_insertions+(removal_amount*(i+1));++j){
                int retcode;
                key = numbers[j];
                element = numbers[j];
                retcode = table.insert_element(key, element);
                REQUIRE(retcode==SUCCESS);
            }
            for(int j=total_insertions+(removal_amount*i);j<total_insertions+(removal_amount*(i+1));++j){
                int retcode;
                key = numbers[j];
                retcode = table.remove_element(key);
                REQUIRE(retcode==SUCCESS);
            }
        }
        test_length.stop_timer();
    }

    SECTION("BST"){
        test_name = "BST_REMOVAL_STRESS";

        auto table = CombinedResizingBST<unsigned,unsigned>(total_insertions, &hash_function);

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){
            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << i);
            retcode = table.insert_element(key, element);
            REQUIRE(retcode==SUCCESS);
        }
        test_length.start_timer();
        INFO("Performing repeated insertion and removal")
        for(int i=0; i<20;i++){
            for(int j=total_insertions+(removal_amount*i);j<total_insertions+(removal_amount*(i+1));++j){
                int retcode;
                key = numbers[j];
                element = numbers[j];
                retcode = table.insert_element(key, element);
                REQUIRE(retcode==SUCCESS);
            }
            for(int j=total_insertions+(removal_amount*i);j<total_insertions+(removal_amount*(i+1));++j){
                int retcode;
                key = numbers[j];
                retcode = table.remove_element(key);
                REQUIRE(retcode==SUCCESS);
            }
        }
        test_length.stop_timer();
    }

    SECTION("RH"){
        test_name = "RH_REMOVAL_STRESS";

        auto table = CombinedResizingRH<unsigned,unsigned>(total_insertions, &hash_function);

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << i);
            retcode = table.insert_element(key, element);
            REQUIRE(retcode==SUCCESS);
        }
        test_length.start_timer();
        INFO("Performing repeated insertion and removal")
        for(int i=0; i<20;i++){
            for(int j=total_insertions+(removal_amount*i);j<total_insertions+(removal_amount*(i+1));++j){
                int retcode;
                key = numbers[j];
                element = numbers[j];
                retcode = table.insert_element(key, element);
                REQUIRE(retcode==SUCCESS);
            }
            for(int j=total_insertions+(removal_amount*i);j<total_insertions+(removal_amount*(i+1));++j){
                int retcode;
                key = numbers[j];
                retcode = table.remove_element(key);
                REQUIRE(retcode==SUCCESS);
            }
        }
        test_length.stop_timer();
    }
    SECTION("CK"){
        test_name = "CK_REMOVAL_STRESS";
        FNV1a<unsigned> hash_function2 = FNV1a<unsigned>();
        hash_function.seed = 2345678901;

        auto table = CombinedResizingCK<unsigned,unsigned>(total_insertions, &hash_function, &hash_function2);

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << i);
            retcode = table.insert_element(key, element);
            REQUIRE(retcode==SUCCESS);
        }
        test_length.start_timer();
        INFO("Performing repeated insertion and removal")
        for(int i=0; i<20;i++){
            for(int j=total_insertions+(removal_amount*i);j<total_insertions+(removal_amount*(i+1));++j){
                int retcode;
                key = numbers[j];
                element = numbers[j];
                retcode = table.insert_element(key, element);
                REQUIRE(retcode==SUCCESS);
            }
            for(int j=total_insertions+(removal_amount*i);j<total_insertions+(removal_amount*(i+1));++j){
                int retcode;
                key = numbers[j];
                retcode = table.remove_element(key);
                REQUIRE(retcode==SUCCESS);
            }
        }
        test_length.stop_timer();
    }

    SECTION("sparse_hash_map"){
        test_name = "sparse_hash_map_removal_STRESS";

        test_length.start_timer();
        auto table = google::sparse_hash_map<unsigned,unsigned>(total_insertions);
        table.set_deleted_key(1);

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << i);
            table[key] = element;
        }
        test_length.start_timer();
        INFO("Performing repeated insertion and removal")
        for(int i=0; i<20;i++){
            for(int j=total_insertions+(removal_amount*i);j<total_insertions+(removal_amount*(i+1));++j){
                int retcode;
                key = numbers[j];
                element = numbers[j];
                table[key] = element;
            }
            for(int j=total_insertions+(removal_amount*i);j<total_insertions+(removal_amount*(i+1));++j){
                int retcode;
                key = numbers[j];
                table.erase(key);
            }
        }
        test_length.stop_timer();
    }

    SECTION("dense_hash_map"){
        test_name = "dense_hash_map_removal_STRESS";

        test_length.start_timer();
        auto table = google::dense_hash_map<unsigned,unsigned>(total_insertions);
        table.set_empty_key(0);
        table.set_deleted_key(1);

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << i);
            table[key] = element;
        }
        test_length.start_timer();
        INFO("Performing repeated insertion and removal")
        for(int i=0; i<20;i++){
            for(int j=total_insertions+(removal_amount*i);j<total_insertions+(removal_amount*(i+1));++j){
                int retcode;
                key = numbers[j];
                element = numbers[j];
                table[key] = element;
            }
            for(int j=total_insertions+(removal_amount*i);j<total_insertions+(removal_amount*(i+1));++j){
                int retcode;
                key = numbers[j];
                table.erase(key);
            }
        }
        test_length.stop_timer();
    }


    statistics.push_back(test_length);


    TestResults output = TestResults(test_name, statistics);
    output.write_results();

}