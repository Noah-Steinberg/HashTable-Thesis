#include "Implementations/hashslot.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <iostream>
using namespace std;

int main(){
    auto logger = spdlog::stdout_color_mt("default");
    auto * testSlot = new HashSlot<int,int>(1,2,3);
    logger->info(testSlot->get_hash());
    logger->info(testSlot->get_key());
    logger->info(testSlot->get_element());
    return 0;
}