//
// Created by nnstein on 17/03/19.
//

#ifndef HASHTABLE_THESIS_MEMORYSIZE_H
#define HASHTABLE_THESIS_MEMORYSIZE_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

inline int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = (int) strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

inline int getMemory(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmSize:", 7) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

#endif //HASHTABLE_THESIS_MEMORYSIZE_H
