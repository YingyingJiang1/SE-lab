#ifndef RUN_PROGRAM_H
#define RUN_PROGRAM_H
#include <map>
#include "../gen-input/genInput.h"

class RunProgram
{
    GenProgramInput input;
public:
    /* run a cpp program n times and the results of each run are saved to the map in the form of numbers and output results, 
    return true for a success run.
    e.g: ouputs[i] is output of the ith execution  */
   bool  runProgram(map<int, string>& outputs);
};

#endif