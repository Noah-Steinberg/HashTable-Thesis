//
// Created by nnstein on 16/02/19.
//

#ifndef HASHTABLE_THESIS_TESTTIMER_H
#define HASHTABLE_THESIS_TESTTIMER_H

#include <time.h>
#include <string>

class TestStatistic {

public:
    clock_t start, finish;
    double value = -1;
    std::string operation;
    std::string unit;
    TestStatistic(std::string operation, std::string unit){
        this->operation = operation;
        this->unit = unit;
    };
    void start_timer(){
        this->start = clock();
    }
    void stop_timer(){
        this->finish = clock();
        this->value = ((double) (this->finish-this->start)) / CLOCKS_PER_SEC;
    }
    void set_value(double value){
        this->value = value;
    }
};


#endif //HASHTABLE_THESIS_TESTTIMER_H
