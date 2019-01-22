#include "spdlog/sinks/stdout_color_sinks.h"
#include "Util/HashSlot.h"
#include "HashFunctions/Hash.h"
#include "Implementations/ChainingLinkedList/BasicChainingLinkedList.h"
#include "Implementations/ChainingBST/BasicChainingBST.h"
#include "Util/BST.h"
#include <iostream>

#include <iterator>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

int main(){

    auto logger = spdlog::stdout_color_mt("default");
    unsigned hash = 1;
    unsigned key = 0;
    unsigned element = 1;
    auto testSlot = HashSlot<unsigned,unsigned>(hash, key, element);
    logger->info(testSlot.get_hash());
    logger->info(testSlot.get_key());
    logger->info(testSlot.get_element());

    ifstream f("../TestData/random.txt");
    istream_iterator<unsigned> start(f), end;
    vector<unsigned> numbers(start, end);
    cout << "Read " << numbers.size() << " numbers" << endl;


    auto table = BasicChainingBST<unsigned,unsigned>(100, Hash<unsigned>());
    for(int i=0; i<1000;++i){
        ostringstream os;
        os << "Inserting element " << numbers[i];
        logger->info(os.str());
        key = numbers[i];
        element = numbers[i];
        table.insert_element(key, element);
        shared_ptr<unsigned> ele;
        table.get_element(key, ele);
        logger->info(*ele);
    }

    /*
    vector<unsigned> toRemove;
    auto BST = BSTTree<unsigned,unsigned>();
    for(int i=0; i<1000;++i)
    {
        if(i % 50 == 0)
        {
            toRemove.push_back(numbers[i]);
        }
        key = numbers[i];
        element = numbers[i];
        shared_ptr<HashSlot<unsigned, unsigned>> hashSlot = make_shared<HashSlot<unsigned, unsigned>>(0, key, element);
        BST.insert(hashSlot);
        shared_ptr<HashSlot<unsigned, unsigned>> slot;
        int ret = BST.get(key, slot);
        assert(ret==0);
        assert(slot->get_element()==element);
    }
    vector<unsigned> removed;
    for (unsigned int i : toRemove) {
        key = i;
        shared_ptr<HashSlot<unsigned, unsigned>> slot;
        removed.push_back(i);
        int ret = BST.remove(key);
        assert(ret==0);
        for(int j=0;j<1000;++j)
        {
            key = numbers[j];
            if(find(removed.begin(), removed.end(), key)!=removed.end())
            {
                ret = BST.get(key, slot);
                BST.get(key, slot);
                assert(ret==-1);
            }
            else
            {
                ret = BST.get(key, slot);
                assert(ret==0);
            }
        }

    }
     */
    return 0;
}