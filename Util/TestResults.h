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
#include "TestStatistic.h"

class TestResults {
    std::vector<TestStatistic> statistics;
    std::string csv_file;
public:
    TestResults(const std::string test_name, std::vector<TestStatistic> statistics){
        time_t now = time(nullptr);
        char* dt = ctime(&now);
        this->csv_file += "../TestResults/";
        this->csv_file += dt;
        this->csv_file += "_";
        this->csv_file += test_name;
        this->csv_file += ".csv";
        this->statistics = std::move(statistics);
    }

    int write_results(){
        std::ofstream f;
        f << std::fixed << std::setprecision(10);
        f.open(this->csv_file);
        f << "Statistic, Value, Units" << endl;
        for(auto it = this->statistics.begin(); it!=this->statistics.end(); ++it){
            f << it.base()->operation << ", " << it.base()->value << ", " << it.base()->unit << endl;
        }
        f.close();
    }
};


#endif //HASHTABLE_THESIS_TESTRESULTS_H
