#include "spdlog/sinks/stdout_color_sinks.h"
#include "Util/HashSlot.h"
#include "HashFunctions/Hash.h"
#include "Implementations/ChainingLinkedList.h"
#include <iostream>
using namespace std;

int main(){
    auto logger = spdlog::stdout_color_mt("default");

    auto * testSlot = new HashSlot<int,int>(1, new int(2), new int(3));
    logger->info(testSlot->get_hash());
    logger->info(*(testSlot->get_key()));
    logger->info(*(testSlot->get_element()));

    int* key = new int(1);

    auto table = new ChainingLinkedList<int,int>(10, new Hash());
    table->insert_element(key, new int(1));
    int* ele = new int(0);
    table->get_element(key, &ele);
    logger->info(*ele);
    return 0;
}