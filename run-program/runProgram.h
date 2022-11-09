#ifndef RUN_PROGRAM_H
#define RUN_PROGRAM_H
#include <map>
#include "../gen-input/genInput.h"

class RunProgram
{
private:
    int n;  // the number of times the program was executed
    string inputFile;   // input of program
    bool compile(string& cppFile);
    void execution(int n, map<int, string>& outputs, ifstream& fin);
public:
    RunProgram(const string& _inputFile, int _n = 1){n = _n, inputFile = _inputFile;}
    
    /* run a cpp program n times and the results of each run are saved to the map in the form of pair(int, string), 
    return true for a success run.
    for a successful run, int is positive; for a failed run, int is negative  
    e.g: pair(1, str) dedicates output of 1th execution is str, pair(-2, NULL) dedicates 2th execution is failed */
   bool  runProgram(string& cppFile, map<int, string>& outputs);
};

#endif