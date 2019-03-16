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
#include "../Util/TestTimer.h"
#include "../Util/TestResults.h"

using namespace std;
TEST_CASE("Basic Sanity Test", "[basic]") {
    // MAX = 10,000,000 (or so)
    unsigned total_insertions = 10000;
    unsigned key;
    unsigned element;
    FNV1a<unsigned> hash_function = FNV1a<unsigned>();
    hash_function.seed = 1234567890;

    ifstream f("../TestData/random.txt");
    istream_iterator<unsigned> start(f), end;
    vector<unsigned> numbers(start, end);

    std::string test_name;
    std::vector<TestTimer> operations = std::vector<TestTimer>();
    TestTimer test_length = TestTimer("Total Time");

    TestTimer longest_inseration = TestTimer("Longest Insertion");
    TestTimer average_insertion = TestTimer("Average Insertion");
    std::vector<TestTimer> all_insertions = std::vector<TestTimer>();

    TestTimer longest_retrieval = TestTimer("Longest Retrieval");
    TestTimer average_retrieval = TestTimer("Average Retrieval");
    std::vector<TestTimer> all_retrievals = std::vector<TestTimer>();

    TestTimer longest_duplicate = TestTimer("Longest Duplicate Check");
    TestTimer average_duplicate = TestTimer("Average Duplicate Check");
    std::vector<TestTimer> all_duplicates = std::vector<TestTimer>();


    TestTimer longest_removal = TestTimer("Longest Removal");
    TestTimer average_removal = TestTimer("Average Removal");
    std::vector<TestTimer> all_removals = std::vector<TestTimer>();

    SECTION("Chained_LL_Table_Test"){
        test_name = "Chained_LL_Table_Test";

        test_length.start_timer();

        auto table = BasicChainingLinkedList<unsigned,unsigned>(total_insertions, &hash_function);

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){
            TestTimer tmp = TestTimer("Longest Insertion");

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if(longest_inseration.seconds_taken < tmp.seconds_taken){
                longest_inseration = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }

        double average_seconds=0;
        for(auto it = all_insertions.begin(); it!=all_insertions.end(); ++it){
            average_seconds += it.base()->seconds_taken;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.seconds_taken = average_seconds;


        INFO("Checking for all elements")
        for(int i=0; i<total_insertions;++i){
            TestTimer tmp = TestTimer("Longest Retrieval");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if(longest_retrieval.seconds_taken < tmp.seconds_taken){
                longest_retrieval = tmp;
            }
            REQUIRE(retcode==SUCCESS);
            REQUIRE(element==ele);
        }

        average_seconds=0;
        for(auto it = all_retrievals.begin(); it!=all_retrievals.end(); ++it){
            average_seconds += it.base()->seconds_taken;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.seconds_taken = average_seconds;

        INFO("Duplicating all elements")
        for(int i=0; i<total_insertions;++i){
            TestTimer tmp = TestTimer("Longest Duplication Check");

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Checking for duplicate key " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_duplicates.push_back(tmp);
            if(longest_duplicate.seconds_taken < tmp.seconds_taken){
                longest_duplicate = tmp;
            }
            REQUIRE(retcode==KEY_ALREADY_EXISTS);
        }
        average_seconds=0;
        for(auto it = all_duplicates.begin(); it!=all_duplicates.end(); ++it){
            average_seconds += it.base()->seconds_taken;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_duplicate.seconds_taken = average_seconds;

        INFO("Removing all elements")
        for(int i=0; i<total_insertions;++i){
            TestTimer tmp = TestTimer("Longest Removal");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Removing element " << element);
            tmp.start_timer();
            retcode = table.remove_element(key);
            tmp.stop_timer();
            all_removals.push_back(tmp);
            if(longest_removal.seconds_taken < tmp.seconds_taken){
                longest_removal = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }
        average_seconds=0;
        for(auto it = all_removals.begin(); it!=all_removals.end(); ++it){
            average_seconds += it.base()->seconds_taken;
        }
        average_seconds = average_seconds / all_removals.size();

        average_removal.seconds_taken = average_seconds;

        INFO("Confirming removal of all elements")
        for(int i=0; i<total_insertions;++i){
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode==KEY_NOT_FOUND);
        }

        test_length.stop_timer();
    }

    SECTION("Chained_BST_Table_Test"){
        test_name = "Chained_BST_Table_Test";

        auto table = BasicChainingBST<unsigned,unsigned>(total_insertions, &hash_function);

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){
            TestTimer tmp = TestTimer("Longest Insertion");

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if(longest_inseration.seconds_taken < tmp.seconds_taken){
                longest_inseration = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }

        double average_seconds=0;
        for(auto it = all_insertions.begin(); it!=all_insertions.end(); ++it){
            average_seconds += it.base()->seconds_taken;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.seconds_taken = average_seconds;


        INFO("Checking for all elements")
        for(int i=0; i<total_insertions;++i){
            TestTimer tmp = TestTimer("Longest Retrieval");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if(longest_retrieval.seconds_taken < tmp.seconds_taken){
                longest_retrieval = tmp;
            }
            REQUIRE(retcode==SUCCESS);
            REQUIRE(element==ele);
        }

        average_seconds=0;
        for(auto it = all_retrievals.begin(); it!=all_retrievals.end(); ++it){
            average_seconds += it.base()->seconds_taken;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.seconds_taken = average_seconds;

        INFO("Duplicating all elements")
        for(int i=0; i<total_insertions;++i){
            TestTimer tmp = TestTimer("Longest Duplication Check");

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Checking for duplicate key " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_duplicates.push_back(tmp);
            if(longest_duplicate.seconds_taken < tmp.seconds_taken){
                longest_duplicate = tmp;
            }
            REQUIRE(retcode==KEY_ALREADY_EXISTS);
        }
        average_seconds=0;
        for(auto it = all_duplicates.begin(); it!=all_duplicates.end(); ++it){
            average_seconds += it.base()->seconds_taken;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_duplicate.seconds_taken = average_seconds;

        INFO("Removing all elements")
        for(int i=0; i<total_insertions;++i){
            TestTimer tmp = TestTimer("Longest Removal");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Removing element " << element);
            tmp.start_timer();
            retcode = table.remove_element(key);
            tmp.stop_timer();
            all_removals.push_back(tmp);
            if(longest_removal.seconds_taken < tmp.seconds_taken){
                longest_removal = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }
        average_seconds=0;
        for(auto it = all_removals.begin(); it!=all_removals.end(); ++it){
            average_seconds += it.base()->seconds_taken;
        }
        average_seconds = average_seconds / all_removals.size();

        average_removal.seconds_taken = average_seconds;

        INFO("Confirming removal of all elements")
        for(int i=0; i<total_insertions;++i){
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode==KEY_NOT_FOUND);
        }

        test_length.stop_timer();
    }

    SECTION("Robin_Hood_Hash_Table_Test"){
        test_name = "Robin_Hood_Hash_Table_Test";

        auto table = BasicRobinHood<unsigned,unsigned>(total_insertions*2, &hash_function);

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){
            TestTimer tmp = TestTimer("Longest Insertion");

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if(longest_inseration.seconds_taken < tmp.seconds_taken){
                longest_inseration = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }

        double average_seconds=0;
        for(auto it = all_insertions.begin(); it!=all_insertions.end(); ++it){
            average_seconds += it.base()->seconds_taken;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.seconds_taken = average_seconds;


        INFO("Checking for all elements")
        for(int i=0; i<total_insertions;++i){
            TestTimer tmp = TestTimer("Longest Retrieval");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if(longest_retrieval.seconds_taken < tmp.seconds_taken){
                longest_retrieval = tmp;
            }
            REQUIRE(retcode==SUCCESS);
            REQUIRE(element==ele);
        }

        average_seconds=0;
        for(auto it = all_retrievals.begin(); it!=all_retrievals.end(); ++it){
            average_seconds += it.base()->seconds_taken;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.seconds_taken = average_seconds;

        INFO("Duplicating all elements")
        for(int i=0; i<total_insertions;++i){
            TestTimer tmp = TestTimer("Longest Duplication Check");

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Checking for duplicate key " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_duplicates.push_back(tmp);
            if(longest_duplicate.seconds_taken < tmp.seconds_taken){
                longest_duplicate = tmp;
            }
            REQUIRE(retcode==KEY_ALREADY_EXISTS);
        }
        average_seconds=0;
        for(auto it = all_duplicates.begin(); it!=all_duplicates.end(); ++it){
            average_seconds += it.base()->seconds_taken;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_duplicate.seconds_taken = average_seconds;

        INFO("Removing all elements")
        for(int i=0; i<total_insertions;++i){
            TestTimer tmp = TestTimer("Longest Removal");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Removing element " << element);
            tmp.start_timer();
            retcode = table.remove_element(key);
            tmp.stop_timer();
            all_removals.push_back(tmp);
            if(longest_removal.seconds_taken < tmp.seconds_taken){
                longest_removal = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }
        average_seconds=0;
        for(auto it = all_removals.begin(); it!=all_removals.end(); ++it){
            average_seconds += it.base()->seconds_taken;
        }
        average_seconds = average_seconds / all_removals.size();

        average_removal.seconds_taken = average_seconds;

        INFO("Confirming removal of all elements")
        for(int i=0; i<total_insertions;++i){
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode==KEY_NOT_FOUND);
        }

        test_length.stop_timer();
    }

    SECTION("Cuckoo_Table_Test"){
        test_name = "Cuckoo_Table_Test";

        Hash<unsigned> hash_function2 = Hash<unsigned>();
        auto table = BasicCuckoo<unsigned,unsigned>(total_insertions, &hash_function, &hash_function2);

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){
            TestTimer tmp = TestTimer("Longest Insertion");

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if(longest_inseration.seconds_taken < tmp.seconds_taken){
                longest_inseration = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }

        double average_seconds=0;
        for(auto it = all_insertions.begin(); it!=all_insertions.end(); ++it){
            average_seconds += it.base()->seconds_taken;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.seconds_taken = average_seconds;


        INFO("Checking for all elements")
        for(int i=0; i<total_insertions;++i){
            TestTimer tmp = TestTimer("Longest Retrieval");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if(longest_retrieval.seconds_taken < tmp.seconds_taken){
                longest_retrieval = tmp;
            }
            REQUIRE(retcode==SUCCESS);
            REQUIRE(element==ele);
        }

        INFO("Inserting duplicate elements")
        for(int i=0; i<total_insertions;++i){
            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            retcode = table.insert_element(key, element);
            REQUIRE(retcode==KEY_ALREADY_EXISTS);
        }

        average_seconds=0;
        for(auto it = all_retrievals.begin(); it!=all_retrievals.end(); ++it){
            average_seconds += it.base()->seconds_taken;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.seconds_taken = average_seconds;

        INFO("Duplicating all elements")
        for(int i=0; i<total_insertions;++i){
            TestTimer tmp = TestTimer("Longest Duplication Check");

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Checking for duplicate key " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_duplicates.push_back(tmp);
            if(longest_duplicate.seconds_taken < tmp.seconds_taken){
                longest_duplicate = tmp;
            }
            REQUIRE(retcode==KEY_ALREADY_EXISTS);
        }
        average_seconds=0;
        for(auto it = all_duplicates.begin(); it!=all_duplicates.end(); ++it){
            average_seconds += it.base()->seconds_taken;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_duplicate.seconds_taken = average_seconds;

        INFO("Removing all elements")
        for(int i=0; i<total_insertions;++i){
            TestTimer tmp = TestTimer("Longest Removal");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Removing element " << element);
            tmp.start_timer();
            retcode = table.remove_element(key);
            tmp.stop_timer();
            all_removals.push_back(tmp);
            if(longest_removal.seconds_taken < tmp.seconds_taken){
                longest_removal = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }
        average_seconds=0;
        for(auto it = all_removals.begin(); it!=all_removals.end(); ++it){
            average_seconds += it.base()->seconds_taken;
        }
        average_seconds = average_seconds / all_removals.size();

        average_removal.seconds_taken = average_seconds;

        INFO("Confirming removal of all elements")
        for(int i=0; i<total_insertions;++i){
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode==KEY_NOT_FOUND);
        }

        test_length.stop_timer();
    }

    operations.push_back(test_length);
    operations.push_back(longest_inseration);
    operations.push_back(average_insertion);
    operations.push_back(longest_retrieval);
    operations.push_back(average_retrieval);
    operations.push_back(longest_duplicate);
    operations.push_back(average_duplicate);
    operations.push_back(longest_removal);
    operations.push_back(average_removal);

    TestResults output = TestResults(test_name, operations);
    output.write_results();

}