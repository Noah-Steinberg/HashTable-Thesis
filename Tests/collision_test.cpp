//
// Created by nnstein on 20/03/19.
//

#include <fstream>
#include <iterator>
#include <iostream>

#include <unordered_map>

#include <sparsehash/sparse_hash_map>
#include <sparsehash/dense_hash_map>

#include "../Util/enums.h"

#include "../Implementations/ChainingLinkedList/BasicChainingLinkedList.h"
#include "../Implementations/ChainingBST/BasicChainingBST.h"
#include "../Implementations/RobinHood/BasicRobinHood.h"
#include "../Implementations/Cuckoo/BasicCuckoo.h"

#include "../Implementations/ChainingLinkedList/ProbeResizingLL.h"
#include "../Implementations/ChainingBST/ProbeResizingBST.h"
#include "../Implementations/Cuckoo/ProbeResizingCK.h"
#include "../Implementations/RobinHood/ProbeResizingRH.h"

#include "../HashFunctions/FNV1a.h"
#include "../HashFunctions/MD5.h"
#include "../HashFunctions/SHA2.h"

#include "../Dependencies/catch.hpp"
#include "../Util/TestStatistic.h"
#include "../Util/TestResults.h"
#include "../Util/MemorySize.h"

using namespace std;

TEST_CASE("Collision Test", "[collision]") {
    unsigned total_insertions = 10000;
    unsigned key;
    unsigned element;
    Hash<unsigned> hash_function = Hash<unsigned>();

    ifstream f("../TestData/collision.txt");
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


    TestStatistic longest_removal = TestStatistic("Longest Removal", "Seconds");
    TestStatistic average_removal = TestStatistic("Average Removal", "Seconds");
    std::vector<TestStatistic> all_removals = std::vector<TestStatistic>();


    SECTION("Chained_LL_Table_Test") {
        test_name = "LL_COLLISION";

        test_length.start_timer();

        auto table = BasicChainingLinkedList<unsigned, unsigned>(total_insertions, &hash_function);

        INFO("Inserting all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if (longest_inseration.value < tmp.value) {
                longest_inseration = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }

        double average_seconds = 0;
        for (auto it = all_insertions.begin(); it != all_insertions.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;


        INFO("Checking for all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if (longest_retrieval.value < tmp.value) {
                longest_retrieval = tmp;
            }
            REQUIRE(retcode == SUCCESS);
            REQUIRE(element == ele);
        }

        average_seconds = 0;
        for (auto it = all_retrievals.begin(); it != all_retrievals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        INFO("Removing all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Removal", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Removing element " << element);
            tmp.start_timer();
            retcode = table.remove_element(key);
            tmp.stop_timer();
            all_removals.push_back(tmp);
            if (longest_removal.value < tmp.value) {
                longest_removal = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }
        average_seconds = 0;
        for (auto it = all_removals.begin(); it != all_removals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_removals.size();

        average_removal.value = average_seconds;

        INFO("Confirming removal of all elements")
        for (int i = 0; i < total_insertions; ++i) {
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode == KEY_NOT_FOUND);
        }

        test_length.stop_timer();
    }
    SECTION("Chained_BST_Table_Test") {
        test_name = "BST_COLLISION";

        test_length.start_timer();

        auto table = BasicChainingBST<unsigned, unsigned>(total_insertions, &hash_function);

        INFO("Inserting all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if (longest_inseration.value < tmp.value) {
                longest_inseration = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }

        double average_seconds = 0;
        for (auto it = all_insertions.begin(); it != all_insertions.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;


        INFO("Checking for all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if (longest_retrieval.value < tmp.value) {
                longest_retrieval = tmp;
            }
            REQUIRE(retcode == SUCCESS);
            REQUIRE(element == ele);
        }

        average_seconds = 0;
        for (auto it = all_retrievals.begin(); it != all_retrievals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        INFO("Removing all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Removal", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Removing element " << element);
            tmp.start_timer();
            retcode = table.remove_element(key);
            tmp.stop_timer();
            all_removals.push_back(tmp);
            if (longest_removal.value < tmp.value) {
                longest_removal = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }
        average_seconds = 0;
        for (auto it = all_removals.begin(); it != all_removals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_removals.size();

        average_removal.value = average_seconds;

        INFO("Confirming removal of all elements")
        for (int i = 0; i < total_insertions; ++i) {
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode == KEY_NOT_FOUND);
        }

        test_length.stop_timer();
    }

    SECTION("Robin_Hood_Hash_Table_Test") {
        test_name = "RH_COLLISION";

        test_length.start_timer();

        auto table = BasicRobinHood<unsigned, unsigned>(total_insertions * 2, &hash_function);

        INFO("Inserting all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if (longest_inseration.value < tmp.value) {
                longest_inseration = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }

        double average_seconds = 0;
        for (auto it = all_insertions.begin(); it != all_insertions.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;


        INFO("Checking for all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if (longest_retrieval.value < tmp.value) {
                longest_retrieval = tmp;
            }
            REQUIRE(retcode == SUCCESS);
            REQUIRE(element == ele);
        }

        average_seconds = 0;
        for (auto it = all_retrievals.begin(); it != all_retrievals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        INFO("Removing all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Removal", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Removing element " << element);
            tmp.start_timer();
            retcode = table.remove_element(key);
            tmp.stop_timer();
            all_removals.push_back(tmp);
            if (longest_removal.value < tmp.value) {
                longest_removal = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }
        average_seconds = 0;
        for (auto it = all_removals.begin(); it != all_removals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_removals.size();

        average_removal.value = average_seconds;

        INFO("Confirming removal of all elements")
        for (int i = 0; i < total_insertions; ++i) {
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode == KEY_NOT_FOUND);
        }

        test_length.stop_timer();
    }

    SECTION("Cuckoo_Table_Test") {
        test_name = "CK_COLLISION";

        test_length.start_timer();

        FNV1a<unsigned> hash_function2 = FNV1a<unsigned>();
        hash_function2.seed = 1234567890;
        auto table = BasicCuckoo<unsigned, unsigned>(total_insertions, &hash_function, &hash_function2);

        INFO("Inserting all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if (longest_inseration.value < tmp.value) {
                longest_inseration = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }

        double average_seconds = 0;
        for (auto it = all_insertions.begin(); it != all_insertions.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;


        INFO("Checking for all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if (longest_retrieval.value < tmp.value) {
                longest_retrieval = tmp;
            }
            REQUIRE(retcode == SUCCESS);
            REQUIRE(element == ele);
        }

        average_seconds = 0;
        for (auto it = all_retrievals.begin(); it != all_retrievals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        INFO("Inserting duplicate elements")
        for (int i = 0; i < total_insertions; ++i) {
            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            retcode = table.insert_element(key, element);
            REQUIRE(retcode == KEY_ALREADY_EXISTS);
        }

        average_seconds = 0;
        for (auto it = all_retrievals.begin(); it != all_retrievals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        INFO("Removing all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Removal", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Removing element " << element);
            tmp.start_timer();
            retcode = table.remove_element(key);
            tmp.stop_timer();
            all_removals.push_back(tmp);
            if (longest_removal.value < tmp.value) {
                longest_removal = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }
        average_seconds = 0;
        for (auto it = all_removals.begin(); it != all_removals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_removals.size();

        average_removal.value = average_seconds;

        INFO("Confirming removal of all elements")
        for (int i = 0; i < total_insertions; ++i) {
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode == KEY_NOT_FOUND);
        }

        test_length.stop_timer();
    }

    statistics.push_back(test_length);
    statistics.push_back(longest_inseration);
    statistics.push_back(average_insertion);
    statistics.push_back(longest_retrieval);
    statistics.push_back(average_retrieval);
    statistics.push_back(longest_removal);
    statistics.push_back(average_removal);

    TestResults output = TestResults(test_name, statistics);
    output.write_results();
}

TEST_CASE("Collision FNV1a Test", "[collision][fnv1a]") {
    unsigned total_insertions = 10000;
    unsigned key;
    unsigned element;
    FNV1a<unsigned> hash_function = FNV1a<unsigned>();
    hash_function.seed = 1234567890;

    ifstream f("../TestData/collision.txt");
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


    TestStatistic longest_removal = TestStatistic("Longest Removal", "Seconds");
    TestStatistic average_removal = TestStatistic("Average Removal", "Seconds");
    std::vector<TestStatistic> all_removals = std::vector<TestStatistic>();


    SECTION("Chained_LL_Table_Test") {
        test_name = "LL_COLLISION";

        test_length.start_timer();

        auto table = BasicChainingLinkedList<unsigned, unsigned>(total_insertions, &hash_function);

        INFO("Inserting all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if (longest_inseration.value < tmp.value) {
                longest_inseration = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }

        double average_seconds = 0;
        for (auto it = all_insertions.begin(); it != all_insertions.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;


        INFO("Checking for all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if (longest_retrieval.value < tmp.value) {
                longest_retrieval = tmp;
            }
            REQUIRE(retcode == SUCCESS);
            REQUIRE(element == ele);
        }

        average_seconds = 0;
        for (auto it = all_retrievals.begin(); it != all_retrievals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        INFO("Removing all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Removal", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Removing element " << element);
            tmp.start_timer();
            retcode = table.remove_element(key);
            tmp.stop_timer();
            all_removals.push_back(tmp);
            if (longest_removal.value < tmp.value) {
                longest_removal = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }
        average_seconds = 0;
        for (auto it = all_removals.begin(); it != all_removals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_removals.size();

        average_removal.value = average_seconds;

        INFO("Confirming removal of all elements")
        for (int i = 0; i < total_insertions; ++i) {
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode == KEY_NOT_FOUND);
        }

        test_length.stop_timer();
    }
    SECTION("Chained_BST_Table_Test") {
        test_name = "BST_COLLISION";

        test_length.start_timer();

        auto table = BasicChainingBST<unsigned, unsigned>(total_insertions, &hash_function);

        INFO("Inserting all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if (longest_inseration.value < tmp.value) {
                longest_inseration = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }

        double average_seconds = 0;
        for (auto it = all_insertions.begin(); it != all_insertions.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;


        INFO("Checking for all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if (longest_retrieval.value < tmp.value) {
                longest_retrieval = tmp;
            }
            REQUIRE(retcode == SUCCESS);
            REQUIRE(element == ele);
        }

        average_seconds = 0;
        for (auto it = all_retrievals.begin(); it != all_retrievals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        INFO("Removing all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Removal", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Removing element " << element);
            tmp.start_timer();
            retcode = table.remove_element(key);
            tmp.stop_timer();
            all_removals.push_back(tmp);
            if (longest_removal.value < tmp.value) {
                longest_removal = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }
        average_seconds = 0;
        for (auto it = all_removals.begin(); it != all_removals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_removals.size();

        average_removal.value = average_seconds;

        INFO("Confirming removal of all elements")
        for (int i = 0; i < total_insertions; ++i) {
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode == KEY_NOT_FOUND);
        }

        test_length.stop_timer();
    }

    SECTION("Robin_Hood_Hash_Table_Test") {
        test_name = "RH_COLLISION";

        test_length.start_timer();

        auto table = BasicRobinHood<unsigned, unsigned>(total_insertions * 2, &hash_function);

        INFO("Inserting all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if (longest_inseration.value < tmp.value) {
                longest_inseration = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }

        double average_seconds = 0;
        for (auto it = all_insertions.begin(); it != all_insertions.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;


        INFO("Checking for all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if (longest_retrieval.value < tmp.value) {
                longest_retrieval = tmp;
            }
            REQUIRE(retcode == SUCCESS);
            REQUIRE(element == ele);
        }

        average_seconds = 0;
        for (auto it = all_retrievals.begin(); it != all_retrievals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        INFO("Removing all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Removal", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Removing element " << element);
            tmp.start_timer();
            retcode = table.remove_element(key);
            tmp.stop_timer();
            all_removals.push_back(tmp);
            if (longest_removal.value < tmp.value) {
                longest_removal = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }
        average_seconds = 0;
        for (auto it = all_removals.begin(); it != all_removals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_removals.size();

        average_removal.value = average_seconds;

        INFO("Confirming removal of all elements")
        for (int i = 0; i < total_insertions; ++i) {
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode == KEY_NOT_FOUND);
        }

        test_length.stop_timer();
    }

    SECTION("Cuckoo_Table_Test") {
        test_name = "CK_COLLISION";

        test_length.start_timer();

        Hash<unsigned> hash_function2 = Hash<unsigned>();
        auto table = BasicCuckoo<unsigned, unsigned>(total_insertions, &hash_function, &hash_function2);

        INFO("Inserting all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if (longest_inseration.value < tmp.value) {
                longest_inseration = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }

        double average_seconds = 0;
        for (auto it = all_insertions.begin(); it != all_insertions.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;


        INFO("Checking for all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if (longest_retrieval.value < tmp.value) {
                longest_retrieval = tmp;
            }
            REQUIRE(retcode == SUCCESS);
            REQUIRE(element == ele);
        }

        average_seconds = 0;
        for (auto it = all_retrievals.begin(); it != all_retrievals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        INFO("Inserting duplicate elements")
        for (int i = 0; i < total_insertions; ++i) {
            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            retcode = table.insert_element(key, element);
            REQUIRE(retcode == KEY_ALREADY_EXISTS);
        }

        average_seconds = 0;
        for (auto it = all_retrievals.begin(); it != all_retrievals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        INFO("Removing all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Removal", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Removing element " << element);
            tmp.start_timer();
            retcode = table.remove_element(key);
            tmp.stop_timer();
            all_removals.push_back(tmp);
            if (longest_removal.value < tmp.value) {
                longest_removal = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }
        average_seconds = 0;
        for (auto it = all_removals.begin(); it != all_removals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_removals.size();

        average_removal.value = average_seconds;

        INFO("Confirming removal of all elements")
        for (int i = 0; i < total_insertions; ++i) {
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode == KEY_NOT_FOUND);
        }

        test_length.stop_timer();
    }

    statistics.push_back(test_length);
    statistics.push_back(longest_inseration);
    statistics.push_back(average_insertion);
    statistics.push_back(longest_retrieval);
    statistics.push_back(average_retrieval);
    statistics.push_back(longest_removal);
    statistics.push_back(average_removal);
    test_name += "_FNV1a";
    TestResults output = TestResults(test_name, statistics);
    output.write_results();
}

TEST_CASE("Collision MD5 Test", "[collision][md5]") {
    unsigned total_insertions = 10000;
    unsigned key;
    unsigned element;
    MD5<unsigned> hash_function = MD5<unsigned>();

    ifstream f("../TestData/collision.txt");
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


    TestStatistic longest_removal = TestStatistic("Longest Removal", "Seconds");
    TestStatistic average_removal = TestStatistic("Average Removal", "Seconds");
    std::vector<TestStatistic> all_removals = std::vector<TestStatistic>();


    SECTION("Chained_LL_Table_Test") {
        test_name = "LL_COLLISION";

        test_length.start_timer();

        auto table = BasicChainingLinkedList<unsigned, unsigned>(total_insertions, &hash_function);

        INFO("Inserting all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if (longest_inseration.value < tmp.value) {
                longest_inseration = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }

        double average_seconds = 0;
        for (auto it = all_insertions.begin(); it != all_insertions.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;


        INFO("Checking for all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if (longest_retrieval.value < tmp.value) {
                longest_retrieval = tmp;
            }
            REQUIRE(retcode == SUCCESS);
            REQUIRE(element == ele);
        }

        average_seconds = 0;
        for (auto it = all_retrievals.begin(); it != all_retrievals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        INFO("Removing all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Removal", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Removing element " << element);
            tmp.start_timer();
            retcode = table.remove_element(key);
            tmp.stop_timer();
            all_removals.push_back(tmp);
            if (longest_removal.value < tmp.value) {
                longest_removal = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }
        average_seconds = 0;
        for (auto it = all_removals.begin(); it != all_removals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_removals.size();

        average_removal.value = average_seconds;

        INFO("Confirming removal of all elements")
        for (int i = 0; i < total_insertions; ++i) {
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode == KEY_NOT_FOUND);
        }

        test_length.stop_timer();
    }
    SECTION("Chained_BST_Table_Test") {
        test_name = "BST_COLLISION";

        test_length.start_timer();

        auto table = BasicChainingBST<unsigned, unsigned>(total_insertions, &hash_function);

        INFO("Inserting all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if (longest_inseration.value < tmp.value) {
                longest_inseration = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }

        double average_seconds = 0;
        for (auto it = all_insertions.begin(); it != all_insertions.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;


        INFO("Checking for all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if (longest_retrieval.value < tmp.value) {
                longest_retrieval = tmp;
            }
            REQUIRE(retcode == SUCCESS);
            REQUIRE(element == ele);
        }

        average_seconds = 0;
        for (auto it = all_retrievals.begin(); it != all_retrievals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        INFO("Removing all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Removal", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Removing element " << element);
            tmp.start_timer();
            retcode = table.remove_element(key);
            tmp.stop_timer();
            all_removals.push_back(tmp);
            if (longest_removal.value < tmp.value) {
                longest_removal = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }
        average_seconds = 0;
        for (auto it = all_removals.begin(); it != all_removals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_removals.size();

        average_removal.value = average_seconds;

        INFO("Confirming removal of all elements")
        for (int i = 0; i < total_insertions; ++i) {
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode == KEY_NOT_FOUND);
        }

        test_length.stop_timer();
    }

    SECTION("Robin_Hood_Hash_Table_Test") {
        test_name = "RH_COLLISION";

        test_length.start_timer();

        auto table = BasicRobinHood<unsigned, unsigned>(total_insertions * 2, &hash_function);

        INFO("Inserting all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if (longest_inseration.value < tmp.value) {
                longest_inseration = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }

        double average_seconds = 0;
        for (auto it = all_insertions.begin(); it != all_insertions.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;


        INFO("Checking for all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if (longest_retrieval.value < tmp.value) {
                longest_retrieval = tmp;
            }
            REQUIRE(retcode == SUCCESS);
            REQUIRE(element == ele);
        }

        average_seconds = 0;
        for (auto it = all_retrievals.begin(); it != all_retrievals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        INFO("Removing all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Removal", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Removing element " << element);
            tmp.start_timer();
            retcode = table.remove_element(key);
            tmp.stop_timer();
            all_removals.push_back(tmp);
            if (longest_removal.value < tmp.value) {
                longest_removal = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }
        average_seconds = 0;
        for (auto it = all_removals.begin(); it != all_removals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_removals.size();

        average_removal.value = average_seconds;

        INFO("Confirming removal of all elements")
        for (int i = 0; i < total_insertions; ++i) {
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode == KEY_NOT_FOUND);
        }

        test_length.stop_timer();
    }

    SECTION("Cuckoo_Table_Test") {
        test_name = "CK_COLLISION";

        test_length.start_timer();

        Hash<unsigned> hash_function2 = Hash<unsigned>();
        auto table = BasicCuckoo<unsigned, unsigned>(total_insertions, &hash_function, &hash_function2);

        INFO("Inserting all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if (longest_inseration.value < tmp.value) {
                longest_inseration = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }

        double average_seconds = 0;
        for (auto it = all_insertions.begin(); it != all_insertions.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;


        INFO("Checking for all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if (longest_retrieval.value < tmp.value) {
                longest_retrieval = tmp;
            }
            REQUIRE(retcode == SUCCESS);
            REQUIRE(element == ele);
        }

        average_seconds = 0;
        for (auto it = all_retrievals.begin(); it != all_retrievals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        INFO("Inserting duplicate elements")
        for (int i = 0; i < total_insertions; ++i) {
            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            retcode = table.insert_element(key, element);
            REQUIRE(retcode == KEY_ALREADY_EXISTS);
        }

        average_seconds = 0;
        for (auto it = all_retrievals.begin(); it != all_retrievals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        INFO("Removing all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Removal", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Removing element " << element);
            tmp.start_timer();
            retcode = table.remove_element(key);
            tmp.stop_timer();
            all_removals.push_back(tmp);
            if (longest_removal.value < tmp.value) {
                longest_removal = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }
        average_seconds = 0;
        for (auto it = all_removals.begin(); it != all_removals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_removals.size();

        average_removal.value = average_seconds;

        INFO("Confirming removal of all elements")
        for (int i = 0; i < total_insertions; ++i) {
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode == KEY_NOT_FOUND);
        }

        test_length.stop_timer();
    }

    statistics.push_back(test_length);
    statistics.push_back(longest_inseration);
    statistics.push_back(average_insertion);
    statistics.push_back(longest_retrieval);
    statistics.push_back(average_retrieval);
    statistics.push_back(longest_removal);
    statistics.push_back(average_removal);
    test_name += "_MD5";
    TestResults output = TestResults(test_name, statistics);
    output.write_results();
}

TEST_CASE("Collision SHA2 Test", "[collision][sha2]") {
    unsigned total_insertions = 10000;
    unsigned key;
    unsigned element;
    SHA2<unsigned> hash_function = SHA2<unsigned>();

    ifstream f("../TestData/collision.txt");
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


    TestStatistic longest_removal = TestStatistic("Longest Removal", "Seconds");
    TestStatistic average_removal = TestStatistic("Average Removal", "Seconds");
    std::vector<TestStatistic> all_removals = std::vector<TestStatistic>();


    SECTION("Chained_LL_Table_Test") {
        test_name = "LL_COLLISION";

        test_length.start_timer();

        auto table = BasicChainingLinkedList<unsigned, unsigned>(total_insertions, &hash_function);

        INFO("Inserting all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if (longest_inseration.value < tmp.value) {
                longest_inseration = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }

        double average_seconds = 0;
        for (auto it = all_insertions.begin(); it != all_insertions.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;


        INFO("Checking for all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if (longest_retrieval.value < tmp.value) {
                longest_retrieval = tmp;
            }
            REQUIRE(retcode == SUCCESS);
            REQUIRE(element == ele);
        }

        average_seconds = 0;
        for (auto it = all_retrievals.begin(); it != all_retrievals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        INFO("Removing all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Removal", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Removing element " << element);
            tmp.start_timer();
            retcode = table.remove_element(key);
            tmp.stop_timer();
            all_removals.push_back(tmp);
            if (longest_removal.value < tmp.value) {
                longest_removal = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }
        average_seconds = 0;
        for (auto it = all_removals.begin(); it != all_removals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_removals.size();

        average_removal.value = average_seconds;

        INFO("Confirming removal of all elements")
        for (int i = 0; i < total_insertions; ++i) {
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode == KEY_NOT_FOUND);
        }

        test_length.stop_timer();
    }
    SECTION("Chained_BST_Table_Test") {
        test_name = "BST_COLLISION";

        test_length.start_timer();

        auto table = BasicChainingBST<unsigned, unsigned>(total_insertions, &hash_function);

        INFO("Inserting all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if (longest_inseration.value < tmp.value) {
                longest_inseration = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }

        double average_seconds = 0;
        for (auto it = all_insertions.begin(); it != all_insertions.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;


        INFO("Checking for all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if (longest_retrieval.value < tmp.value) {
                longest_retrieval = tmp;
            }
            REQUIRE(retcode == SUCCESS);
            REQUIRE(element == ele);
        }

        average_seconds = 0;
        for (auto it = all_retrievals.begin(); it != all_retrievals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        INFO("Removing all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Removal", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Removing element " << element);
            tmp.start_timer();
            retcode = table.remove_element(key);
            tmp.stop_timer();
            all_removals.push_back(tmp);
            if (longest_removal.value < tmp.value) {
                longest_removal = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }
        average_seconds = 0;
        for (auto it = all_removals.begin(); it != all_removals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_removals.size();

        average_removal.value = average_seconds;

        INFO("Confirming removal of all elements")
        for (int i = 0; i < total_insertions; ++i) {
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode == KEY_NOT_FOUND);
        }

        test_length.stop_timer();
    }

    SECTION("Robin_Hood_Hash_Table_Test") {
        test_name = "RH_COLLISION";

        test_length.start_timer();

        auto table = BasicRobinHood<unsigned, unsigned>(total_insertions * 2, &hash_function);

        INFO("Inserting all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if (longest_inseration.value < tmp.value) {
                longest_inseration = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }

        double average_seconds = 0;
        for (auto it = all_insertions.begin(); it != all_insertions.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;


        INFO("Checking for all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if (longest_retrieval.value < tmp.value) {
                longest_retrieval = tmp;
            }
            REQUIRE(retcode == SUCCESS);
            REQUIRE(element == ele);
        }

        average_seconds = 0;
        for (auto it = all_retrievals.begin(); it != all_retrievals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        INFO("Removing all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Removal", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Removing element " << element);
            tmp.start_timer();
            retcode = table.remove_element(key);
            tmp.stop_timer();
            all_removals.push_back(tmp);
            if (longest_removal.value < tmp.value) {
                longest_removal = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }
        average_seconds = 0;
        for (auto it = all_removals.begin(); it != all_removals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_removals.size();

        average_removal.value = average_seconds;

        INFO("Confirming removal of all elements")
        for (int i = 0; i < total_insertions; ++i) {
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode == KEY_NOT_FOUND);
        }

        test_length.stop_timer();
    }

    SECTION("Cuckoo_Table_Test") {
        test_name = "CK_COLLISION";

        test_length.start_timer();

        MD5<unsigned> hash_function2 = MD5<unsigned>();
        auto table = BasicCuckoo<unsigned, unsigned>(total_insertions, &hash_function, &hash_function2);

        INFO("Inserting all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            tmp.start_timer();
            retcode = table.insert_element(key, element);
            tmp.stop_timer();
            all_insertions.push_back(tmp);
            if (longest_inseration.value < tmp.value) {
                longest_inseration = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }

        double average_seconds = 0;
        for (auto it = all_insertions.begin(); it != all_insertions.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_insertions.size();

        average_insertion.value = average_seconds;


        INFO("Checking for all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            tmp.start_timer();
            retcode = table.get_element(key, ele);
            tmp.stop_timer();
            all_retrievals.push_back(tmp);
            if (longest_retrieval.value < tmp.value) {
                longest_retrieval = tmp;
            }
            REQUIRE(retcode == SUCCESS);
            REQUIRE(element == ele);
        }

        average_seconds = 0;
        for (auto it = all_retrievals.begin(); it != all_retrievals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        INFO("Inserting duplicate elements")
        for (int i = 0; i < total_insertions; ++i) {
            int retcode;
            key = numbers[i];
            element = numbers[i];
            INFO("Inserting element " << element);
            retcode = table.insert_element(key, element);
            REQUIRE(retcode == KEY_ALREADY_EXISTS);
        }

        average_seconds = 0;
        for (auto it = all_retrievals.begin(); it != all_retrievals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_retrievals.size();
        average_retrieval.value = average_seconds;

        INFO("Removing all elements")
        for (int i = 0; i < total_insertions; ++i) {
            TestStatistic tmp = TestStatistic("Longest Removal", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Removing element " << element);
            tmp.start_timer();
            retcode = table.remove_element(key);
            tmp.stop_timer();
            all_removals.push_back(tmp);
            if (longest_removal.value < tmp.value) {
                longest_removal = tmp;
            }
            REQUIRE(retcode == SUCCESS);
        }
        average_seconds = 0;
        for (auto it = all_removals.begin(); it != all_removals.end(); ++it) {
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_removals.size();

        average_removal.value = average_seconds;

        INFO("Confirming removal of all elements")
        for (int i = 0; i < total_insertions; ++i) {
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Checking for element " << element);
            retcode = table.get_element(key, ele);
            REQUIRE(retcode == KEY_NOT_FOUND);
        }

        test_length.stop_timer();
    }

    statistics.push_back(test_length);
    statistics.push_back(longest_inseration);
    statistics.push_back(average_insertion);
    statistics.push_back(longest_retrieval);
    statistics.push_back(average_retrieval);
    statistics.push_back(longest_removal);
    statistics.push_back(average_removal);
    test_name += "_SHA2";
    TestResults output = TestResults(test_name, statistics);
    output.write_results();
}

TEST_CASE("Probe Resize Collision Test", "[probe][collision]") {
    unsigned total_insertions = 10000;
    unsigned key;
    unsigned element;
    Hash<unsigned> hash_function = Hash<unsigned>();

    ifstream f("../TestData/collision.txt");
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

    TestStatistic longest_removal = TestStatistic("Longest Removal", "Seconds");
    TestStatistic average_removal = TestStatistic("Average Removal", "Seconds");
    std::vector<TestStatistic> all_removals = std::vector<TestStatistic>();


    SECTION("Chained_LL_Table_Test"){
        test_name = "LL_PROBE_COLLISION";

        test_length.start_timer();

        auto table = ProbeResizingLL<unsigned,unsigned>(total_insertions, &hash_function);

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            int retcode;
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


        INFO("Checking for all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");
            int retcode;
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

        INFO("Removing all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Removal", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Removing element " << element);
            tmp.start_timer();
            retcode = table.remove_element(key);
            tmp.stop_timer();
            all_removals.push_back(tmp);
            if(longest_removal.value < tmp.value){
                longest_removal = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }
        average_seconds=0;
        for(auto it = all_removals.begin(); it!=all_removals.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_removals.size();

        average_removal.value = average_seconds;

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
        test_name = "BST_PROBE_COLLISION";

        test_length.start_timer();

        auto table = ProbeResizingBST<unsigned,unsigned>(total_insertions, &hash_function);

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            int retcode;
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


        INFO("Checking for all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");
            int retcode;
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

        INFO("Removing all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Removal", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Removing element " << element);
            tmp.start_timer();
            retcode = table.remove_element(key);
            tmp.stop_timer();
            all_removals.push_back(tmp);
            if(longest_removal.value < tmp.value){
                longest_removal = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }
        average_seconds=0;
        for(auto it = all_removals.begin(); it!=all_removals.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_removals.size();

        average_removal.value = average_seconds;

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
        test_name = "RH_PROBE_COLLISION";

        test_length.start_timer();

        auto table = ProbeResizingRH<unsigned,unsigned>(total_insertions, &hash_function);

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            int retcode;
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


        INFO("Checking for all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");
            int retcode;
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

        INFO("Removing all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Removal", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Removing element " << element);
            tmp.start_timer();
            retcode = table.remove_element(key);
            tmp.stop_timer();
            all_removals.push_back(tmp);
            if(longest_removal.value < tmp.value){
                longest_removal = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }
        average_seconds=0;
        for(auto it = all_removals.begin(); it!=all_removals.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_removals.size();

        average_removal.value = average_seconds;

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
        test_name = "CK_PROBE_COLLISION";

        test_length.start_timer();

        FNV1a<unsigned> hash_function2 = FNV1a<unsigned>();
        hash_function2.seed = 1234567890;
        auto table = ProbeResizingCK<unsigned,unsigned>(total_insertions, &hash_function, &hash_function2);

        INFO("Inserting all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Insertion", "Seconds");

            int retcode;
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


        INFO("Checking for all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Retrieval", "Seconds");
            int retcode;
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


        INFO("Removing all elements")
        for(int i=0; i<total_insertions;++i){
            TestStatistic tmp = TestStatistic("Longest Removal", "Seconds");
            int retcode;
            key = numbers[i];
            element = numbers[i];
            unsigned ele;
            INFO("Removing element " << element);
            tmp.start_timer();
            retcode = table.remove_element(key);
            tmp.stop_timer();
            all_removals.push_back(tmp);
            if(longest_removal.value < tmp.value){
                longest_removal = tmp;
            }
            REQUIRE(retcode==SUCCESS);
        }
        average_seconds=0;
        for(auto it = all_removals.begin(); it!=all_removals.end(); ++it){
            average_seconds += it.base()->value;
        }
        average_seconds = average_seconds / all_removals.size();

        average_removal.value = average_seconds;

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

    statistics.push_back(test_length);
    statistics.push_back(longest_inseration);
    statistics.push_back(average_insertion);
    statistics.push_back(longest_retrieval);
    statistics.push_back(average_retrieval);
    statistics.push_back(longest_removal);
    statistics.push_back(average_removal);

    TestResults output = TestResults(test_name, statistics);
    output.write_results();

}