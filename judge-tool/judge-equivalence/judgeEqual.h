#ifndef JUDGE_EQUAL_H
#define JUDGE_EQUAL_H
#include "../run-program/runProgram.h"
#include <string>
using std::string;

/*
function of class JudgeEqual:
cppFiles stores filename of  n cpp files, determine whether every two files are equivalent.
Output each pair of equivalent files to 'equal.csv', output each pair of inequivalent files to 'inequal.csv'.
*/

class JudgeEqual
{
public:
    // compare m1 and m2, if m1 and m2 are the same then return 1
    int equivalence(map<int, string>& m1, map<int, string>& m2);

};

#endif