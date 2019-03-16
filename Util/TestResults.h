#include <utility>

//
// Created by nnstein on 16/02/19.
//

#ifndef HASHTABLE_THESIS_TESTRESULTS_H
#define HASHTABLE_THESIS_TESTRESULTS_H


#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "TestTimer.h"

class TestResults {
    std::vector<TestTimer> operations;
    std::string csv_file;
public:
    TestResults(const std::string test_name, std::vector<TestTimer> operations){
        time_t now = time(nullptr);
        char* dt = ctime(&now);
        this->csv_file = "../TestResults/" + test_name + dt + ".csv";
        this->operations = std::move(operations);
    }

    int write_results(){
        std::ofstream f;
        f << std::fixed << std::setprecision(10);
        f.open(this->csv_file);
        f << "Operation, Seconds Taken" << endl;
        for(auto it = this->operations.begin(); it!=this->operations.end(); ++it){
            f << it.base()->operation << ", " << it.base()->seconds_taken << endl;
        }
        f.close();
    }
};


#endif //HASHTABLE_THESIS_TESTRESULTS_H
