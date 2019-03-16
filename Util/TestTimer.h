//
// Created by nnstein on 16/02/19.
//

#ifndef HASHTABLE_THESIS_TESTTIMER_H
#define HASHTABLE_THESIS_TESTTIMER_H

#include <time.h>
#include <string>

class TestTimer {

public:
    clock_t start, finish;
    double seconds_taken = -1;
    std::string operation;
    TestTimer(std::string operation){
        this->operation = operation;
    };
    void start_timer(){
        this->start = clock();
    }
    void stop_timer(){
        this->finish = clock();
        this->seconds_taken = ((double) (this->finish-this->start)) / CLOCKS_PER_SEC;
    }
};


#endif //HASHTABLE_THESIS_TESTTIMER_H
