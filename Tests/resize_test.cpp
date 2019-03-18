//
// Created by nnstein on 16/03/19.
//

#include <fstream>
#include <iterator>
#include <iostream>

#include "../Util/enums.h"

#include "../Implementations/ChainingLinkedList/CombinedResizingLL.h"
#include "../Implementations/ChainingLinkedList/LoadResizingLL.h"
#include "../Implementations/ChainingLinkedList/ProbeResizingLL.h"

#include "../Implementations/ChainingBST/CombinedResizingBST.h"
#include "../Implementations/ChainingBST/LoadResizingBST.h"
#include "../Implementations/ChainingBST/ProbeResizingBST.h"

#include "../Implementations/Cuckoo/CombinedResizingCK.h"
#include "../Implementations/Cuckoo/LoadResizingCK.h"
#include "../Implementations/Cuckoo/ProbeResizingCK.h"

#include "../Implementations/RobinHood/CombinedResizingRH.h"
#include "../Implementations/RobinHood/LoadResizingRH.h"
#include "../Implementations/RobinHood/ProbeResizingRH.h"

#include "../HashFunctions/FNV1a.h"

#include "catch.hpp"
#include "../Util/TestStatistic.h"
#include "../Util/TestResults.h"
#include "../Util/MemorySize.h"

using namespace std;
TEST_CASE("Load Resize Test", "[loadresize]") {
    unsigned total_insertions = 1000000;
    double max_load = 0.9;
    unsigned key;
    unsigned element;
    FNV1a<unsigned> hash_function = FNV1a<unsigned>();
    hash_function.seed = 1234567890;

    ifstream f("../TestData/random.txt");
    istream_iterator<unsigned> start(f), end;
    vector<unsigned> numbers(start, end);

    std::string test_name;
    std::vector<TestStatistic> statistics = std::vector<TestStatistic>();
    TestStatistic test_length = TestStatistic("Total Time", "Seconds");

    TestStatistic longest_inseration = TestStatistic("Longest Insertion", "Seconds");
    TestStatistic average_insertion = TestStatistic("Average Insertion", "Seconds");
    std::vector<TestStatistic> all_insertions = std::vector<TestStatistic>();

    TestStatistic longest_retrieval = TestStatistic("Longest Retrieval", "Seconds");
    TestStatistic average_retrieval = TestStatistic("Average Retrieval", "Seconds");
    std::vector<TestStatistic> all_retrievals = std::vector<TestStatistic>();

    TestStatistic resize_time = TestStatistic("Resize Time", "Seconds");

    TestStatistic memory_size = TestStatistic("Max Memory Usage", "KiloBytes");
    TestStatistic base_memory_size = TestStatistic("Initial Memory Usage", "KiloBytes");
    TestStatistic init_memory_size = TestStatistic("Initial Memory Usage", "KiloBytes");
    init_memory_size.set_value((double) getMemory());

    SECTION("LinkedList_Test"){
        test_name = "LL_LOADRESIZE";

        test_length.start_timer();

        auto table = LoadResizingLL<unsigned, unsigned>(total_insertions, &hash_function, max_load);
        base_memory_size.set_value((double) getMemory());
        int retcode;

        INFO("Inserting initial elements")
        for(int i=0; i<(int) (max_load*total_insertions-1);++i){
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if(longest_inseration.value < tmp.value){
                longest_inseration = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }

        INFO("Inserting element to trigger resize");
        int index = (int)  (max_load*total_insertions-1);
        key = numbers[index];
        element = numbers[index];
        resize_time.start_timer();
        retcode = table.insert_element(key, element);
        resize_time.stop_timer();
        REQUIRE(retcode==SUCCESS);

        INFO("Inserting remaining elements")
        for(int i=(int) (max_load*total_insertions); i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if(longest_inseration.value < tmp.value){
                longest_inseration = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }

        double average_seconds=0;
        for(auto it = all_insertions.begin(); it!=all_insertions.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;

        memory_size.set_value((double) getMemory());

        INFO("Checking for all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");

            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if(longest_retrieval.value < tmp.value){
                longest_retrieval = tmp;
            }
            REQUIRE(retcode==SUCCESS);
            REQUIRE(element==ele);
        }

        average_seconds=0;
        for(auto it = all_retrievals.begin(); it!=all_retrievals.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        test_length.stop_timer();
    }

    SECTION("BST_Table_Test"){
        test_name = "BST_LOADRESIZE";

        test_length.start_timer();

        auto table = LoadResizingBST<unsigned, unsigned>(total_insertions, &hash_function, max_load);
        base_memory_size.set_value((double) getMemory());
        int retcode;

        INFO("Inserting initial elements")
        for(int i=0; i<(int) (max_load*total_insertions-1);++i){
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if(longest_inseration.value < tmp.value){
                longest_inseration = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }

        INFO("Inserting element to trigger resize");
        int index = (int)  (max_load*total_insertions-1);
        key = numbers[index];
        element = numbers[index];
        resize_time.start_timer();
        retcode = table.insert_element(key, element);
        resize_time.stop_timer();
        REQUIRE(retcode==SUCCESS);

        INFO("Inserting remaining elements")
        for(int i=(int) (max_load*total_insertions); i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if(longest_inseration.value < tmp.value){
                longest_inseration = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }

        double average_seconds=0;
        for(auto it = all_insertions.begin(); it!=all_insertions.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;

        memory_size.set_value((double) getMemory());

        INFO("Checking for all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");

            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if(longest_retrieval.value < tmp.value){
                longest_retrieval = tmp;
            }
            REQUIRE(retcode==SUCCESS);
            REQUIRE(element==ele);
        }

        average_seconds=0;
        for(auto it = all_retrievals.begin(); it!=all_retrievals.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        test_length.stop_timer();

    }

    SECTION("Robin_Hood_Test"){
        test_name = "RH_LOADRESIZE";
        test_length.start_timer();

        auto table = LoadResizingRH<unsigned, unsigned>(total_insertions, &hash_function, max_load);
        base_memory_size.set_value((double) getMemory());
        int retcode;

        INFO("Inserting initial elements")
        for(int i=0; i<(int) (max_load*total_insertions-1);++i){
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if(longest_inseration.value < tmp.value){
                longest_inseration = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }

        INFO("Inserting element to trigger resize");
        int index = (int)  (max_load*total_insertions-1);
        key = numbers[index];
        element = numbers[index];
        resize_time.start_timer();
        retcode = table.insert_element(key, element);
        resize_time.stop_timer();
        REQUIRE(retcode==SUCCESS);

        INFO("Inserting remaining elements")
        for(int i=(int) (max_load*total_insertions); i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if(longest_inseration.value < tmp.value){
                longest_inseration = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }

        double average_seconds=0;
        for(auto it = all_insertions.begin(); it!=all_insertions.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;

        memory_size.set_value((double) getMemory());

        INFO("Checking for all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");

            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if(longest_retrieval.value < tmp.value){
                longest_retrieval = tmp;
            }
            REQUIRE(retcode==SUCCESS);
            REQUIRE(element==ele);
        }

        average_seconds=0;
        for(auto it = all_retrievals.begin(); it!=all_retrievals.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        test_length.stop_timer();

    }

    SECTION("Cuckoo_Table_Test"){
        test_name = "CK_LOADRESIZE";

        test_length.start_timer();

        Hash<unsigned> hash_function2 = Hash<unsigned>();
        auto table = LoadResizingCK<unsigned, unsigned>(total_insertions, &hash_function, &hash_function2, max_load);
        base_memory_size.set_value((double) getMemory());
        int retcode;

        INFO("Inserting initial elements")
        for(int i=0; i<(int) (max_load*total_insertions-1);++i){
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if(longest_inseration.value < tmp.value){
                longest_inseration = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }

        INFO("Inserting element to trigger resize");
        int index = (int)  (max_load*total_insertions-1);
        key = numbers[index];
        element = numbers[index];
        resize_time.start_timer();
        retcode = table.insert_element(key, element);
        resize_time.stop_timer();
        REQUIRE(retcode==SUCCESS);

        INFO("Inserting remaining elements")
        for(int i=(int) (max_load*total_insertions); i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if(longest_inseration.value < tmp.value){
                longest_inseration = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }

        double average_seconds=0;
        for(auto it = all_insertions.begin(); it!=all_insertions.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;

        memory_size.set_value((double) getMemory());

        INFO("Checking for all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");

            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if(longest_retrieval.value < tmp.value){
                longest_retrieval = tmp;
            }
            REQUIRE(retcode==SUCCESS);
            REQUIRE(element==ele);
        }

        average_seconds=0;
        for(auto it = all_retrievals.begin(); it!=all_retrievals.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        test_length.stop_timer();

    }

    statistics.push_back(test_length);
    statistics.push_back(longest_inseration);
    statistics.push_back(average_insertion);
    statistics.push_back(longest_retrieval);
    statistics.push_back(average_retrieval);
    statistics.push_back(resize_time);
    statistics.push_back(base_memory_size);
    statistics.push_back(memory_size);

    TestResults output = TestResults(test_name, statistics);
    output.write_results();
}


TEST_CASE("Probe Resize Test", "[proberesize]") {
    unsigned total_insertions = 1000000;
    int max_chain = (int) log2(total_insertions);
    unsigned key;
    unsigned element;
    FNV1a<unsigned> hash_function = FNV1a<unsigned>();
    hash_function.seed = 1234567890;

    ifstream f("../TestData/random.txt");
    istream_iterator<unsigned> start(f), end;
    vector<unsigned> numbers(start, end);

    std::string test_name;
    std::vector<TestStatistic> statistics = std::vector<TestStatistic>();
    TestStatistic test_length = TestStatistic("Total Time", "Seconds");

    TestStatistic longest_inseration = TestStatistic("Longest Insertion", "Seconds");
    TestStatistic average_insertion = TestStatistic("Average Insertion", "Seconds");
    std::vector<TestStatistic> all_insertions = std::vector<TestStatistic>();

    TestStatistic longest_retrieval = TestStatistic("Longest Retrieval", "Seconds");
    TestStatistic average_retrieval = TestStatistic("Average Retrieval", "Seconds");
    std::vector<TestStatistic> all_retrievals = std::vector<TestStatistic>();

    TestStatistic memory_size = TestStatistic("Max Memory Usage", "KiloBytes");
    TestStatistic base_memory_size = TestStatistic("Initial Memory Usage", "KiloBytes");

    SECTION("LinkedList_Test"){
        test_name = "LL_PROBERESIZE";

        test_length.start_timer();

        auto table = ProbeResizingLL<unsigned, unsigned>(total_insertions/8, &hash_function, max_chain);
        base_memory_size.set_value((double) getMemory());
        int retcode;

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if(longest_inseration.value < tmp.value){
                longest_inseration = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }

        double average_seconds=0;
        for(auto it = all_insertions.begin(); it!=all_insertions.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;

        memory_size.set_value((double) getMemory());

        INFO("Checking for all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");

            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if(longest_retrieval.value < tmp.value){
                longest_retrieval = tmp;
            }
            REQUIRE(retcode==SUCCESS);
            REQUIRE(element==ele);
        }

        average_seconds=0;
        for(auto it = all_retrievals.begin(); it!=all_retrievals.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        test_length.stop_timer();
    }

    SECTION("BST_Table_Test"){
        test_name = "BST_PROBERESIZE";

        test_length.start_timer();

        auto table = ProbeResizingBST<unsigned, unsigned>(total_insertions/8, &hash_function, max_chain);
        base_memory_size.set_value((double) getMemory());
        int retcode;

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if(longest_inseration.value < tmp.value){
                longest_inseration = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }

        double average_seconds=0;
        for(auto it = all_insertions.begin(); it!=all_insertions.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;

        memory_size.set_value((double) getMemory());

        INFO("Checking for all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");

            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if(longest_retrieval.value < tmp.value){
                longest_retrieval = tmp;
            }
            REQUIRE(retcode==SUCCESS);
            REQUIRE(element==ele);
        }

        average_seconds=0;
        for(auto it = all_retrievals.begin(); it!=all_retrievals.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        test_length.stop_timer();

    }

    SECTION("Robin_Hood_Test"){
        test_name = "RH_PROBERESIZE";
        test_length.start_timer();

        auto table = ProbeResizingRH<unsigned, unsigned>(total_insertions/8, &hash_function, max_chain);
        base_memory_size.set_value((double) getMemory());
        int retcode;

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if(longest_inseration.value < tmp.value){
                longest_inseration = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }

        double average_seconds=0;
        for(auto it = all_insertions.begin(); it!=all_insertions.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;

        memory_size.set_value((double) getMemory());

        INFO("Checking for all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");

            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if(longest_retrieval.value < tmp.value){
                longest_retrieval = tmp;
            }
            REQUIRE(retcode==SUCCESS);
            REQUIRE(element==ele);
        }

        average_seconds=0;
        for(auto it = all_retrievals.begin(); it!=all_retrievals.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        test_length.stop_timer();

    }

    SECTION("Cuckoo_Table_Test"){
        test_name = "CK_PROBERESIZE";

        test_length.start_timer();

        Hash<unsigned> hash_function2 = Hash<unsigned>();
        auto table = ProbeResizingCK<unsigned, unsigned>(total_insertions/8, &hash_function, &hash_function2, max_chain);
        base_memory_size.set_value((double) getMemory());
        int retcode;

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if(longest_inseration.value < tmp.value){
                longest_inseration = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }

        double average_seconds=0;
        for(auto it = all_insertions.begin(); it!=all_insertions.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;

        memory_size.set_value((double) getMemory());

        INFO("Checking for all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");

            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if(longest_retrieval.value < tmp.value){
                longest_retrieval = tmp;
            }
            REQUIRE(retcode==SUCCESS);
            REQUIRE(element==ele);
        }

        average_seconds=0;
        for(auto it = all_retrievals.begin(); it!=all_retrievals.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        test_length.stop_timer();

    }

    statistics.push_back(test_length);
    statistics.push_back(longest_inseration);
    statistics.push_back(average_insertion);
    statistics.push_back(longest_retrieval);
    statistics.push_back(average_retrieval);
    statistics.push_back(base_memory_size);
    statistics.push_back(memory_size);

    TestResults output = TestResults(test_name, statistics);
    output.write_results();
}


TEST_CASE("Combined Resize Test", "[combinedresize]") {
    unsigned total_insertions = 1000000;
    int max_chain = (int) log2(total_insertions);
    double chain_max_load = 2.0;
    double open_max_load = 0.9;
    unsigned key;
    unsigned element;
    FNV1a<unsigned> hash_function = FNV1a<unsigned>();
    hash_function.seed = 1234567890;

    ifstream f("../TestData/random.txt");
    istream_iterator<unsigned> start(f), end;
    vector<unsigned> numbers(start, end);

    std::string test_name;
    std::vector<TestStatistic> statistics = std::vector<TestStatistic>();
    TestStatistic test_length = TestStatistic("Total Time", "Seconds");

    TestStatistic longest_inseration = TestStatistic("Longest Insertion", "Seconds");
    TestStatistic average_insertion = TestStatistic("Average Insertion", "Seconds");
    std::vector<TestStatistic> all_insertions = std::vector<TestStatistic>();

    TestStatistic longest_retrieval = TestStatistic("Longest Retrieval", "Seconds");
    TestStatistic average_retrieval = TestStatistic("Average Retrieval", "Seconds");
    std::vector<TestStatistic> all_retrievals = std::vector<TestStatistic>();

    TestStatistic memory_size = TestStatistic("Max Memory Usage", "KiloBytes");
    TestStatistic base_memory_size = TestStatistic("Initial Memory Usage", "KiloBytes");

    SECTION("LinkedList_Test"){
        test_name = "LL_COMBINEDRESIZE";

        test_length.start_timer();

        auto table = CombinedResizingLL<unsigned, unsigned>(total_insertions/8, &hash_function, chain_max_load, max_chain);
        base_memory_size.set_value((double) getMemory());
        int retcode;

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if(longest_inseration.value < tmp.value){
                longest_inseration = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }

        double average_seconds=0;
        for(auto it = all_insertions.begin(); it!=all_insertions.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;

        memory_size.set_value((double) getMemory());

        INFO("Checking for all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");

            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if(longest_retrieval.value < tmp.value){
                longest_retrieval = tmp;
            }
            REQUIRE(retcode==SUCCESS);
            REQUIRE(element==ele);
        }

        average_seconds=0;
        for(auto it = all_retrievals.begin(); it!=all_retrievals.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        test_length.stop_timer();
    }

    SECTION("BST_Table_Test"){
        test_name = "BST_COMBINEDRESIZE";

        test_length.start_timer();

        auto table = CombinedResizingBST<unsigned, unsigned>(total_insertions/8, &hash_function, chain_max_load, max_chain);
        base_memory_size.set_value((double) getMemory());
        int retcode;

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if(longest_inseration.value < tmp.value){
                longest_inseration = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }

        double average_seconds=0;
        for(auto it = all_insertions.begin(); it!=all_insertions.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;

        memory_size.set_value((double) getMemory());

        INFO("Checking for all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");

            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if(longest_retrieval.value < tmp.value){
                longest_retrieval = tmp;
            }
            REQUIRE(retcode==SUCCESS);
            REQUIRE(element==ele);
        }

        average_seconds=0;
        for(auto it = all_retrievals.begin(); it!=all_retrievals.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        test_length.stop_timer();

    }

    SECTION("Robin_Hood_Test"){
        test_name = "RH_COMBINEDRESIZE";
        test_length.start_timer();

        auto table = CombinedResizingRH<unsigned, unsigned>(total_insertions/8, &hash_function, open_max_load, max_chain);
        base_memory_size.set_value((double) getMemory());
        int retcode;

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if(longest_inseration.value < tmp.value){
                longest_inseration = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }

        double average_seconds=0;
        for(auto it = all_insertions.begin(); it!=all_insertions.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;

        memory_size.set_value((double) getMemory());

        INFO("Checking for all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");

            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if(longest_retrieval.value < tmp.value){
                longest_retrieval = tmp;
            }
            REQUIRE(retcode==SUCCESS);
            REQUIRE(element==ele);
        }

        average_seconds=0;
        for(auto it = all_retrievals.begin(); it!=all_retrievals.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        test_length.stop_timer();

    }

    SECTION("Cuckoo_Table_Test"){
        test_name = "CK_COMBINEDRESIZE";

        test_length.start_timer();

        Hash<unsigned> hash_function2 = Hash<unsigned>();
        auto table = CombinedResizingCK<unsigned, unsigned>(total_insertions/8, &hash_function, &hash_function2, open_max_load, max_chain);
        base_memory_size.set_value((double) getMemory());
        int retcode;

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if(longest_inseration.value < tmp.value){
                longest_inseration = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }

        double average_seconds=0;
        for(auto it = all_insertions.begin(); it!=all_insertions.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;

        memory_size.set_value((double) getMemory());

        INFO("Checking for all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");

            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if(longest_retrieval.value < tmp.value){
                longest_retrieval = tmp;
            }
            REQUIRE(retcode==SUCCESS);
            REQUIRE(element==ele);
        }

        average_seconds=0;
        for(auto it = all_retrievals.begin(); it!=all_retrievals.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        test_length.stop_timer();

    }

    statistics.push_back(test_length);
    statistics.push_back(longest_inseration);
    statistics.push_back(average_insertion);
    statistics.push_back(longest_retrieval);
    statistics.push_back(average_retrieval);
    statistics.push_back(init_memory_size);
    statistics.push_back(base_memory_size);
    statistics.push_back(memory_size);

    TestResults output = TestResults(test_name, statistics);
    output.write_results();
}
