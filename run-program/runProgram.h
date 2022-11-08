#ifndef RUN_PROGRAM_H
#define RUN_PROGRAM_H
#include <map>
#include "../gen-input/genInput.h"

class RunProgram
{
public:
    /* run a cpp program n times and the results of each run are saved to the map in the form of pair(int, string), 
    return true for a success run.
    for a successful run, int is positive; for a failed run, int is negative  
    e.g: pair(1, str) dedicates output of 1th execution is str, pair(-2, NULL) dedicates 2th execution is failed */
   bool  runProgram(string& cppFile, string& inputFile, map<int, string>& outputs, int n);
};

#endif