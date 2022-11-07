#include "judgeEqual.h"

int JudgeEqual::judgeEquivalence(string& file1, string& file2, string& inputFormatFile)
{
    RunProgram run;
    GenProgramInput input(inputFormatFile);

    string inputFile = "input.txt";
    map<int, string> outfile1, outfile2;
    input.genInput(100, inputFile);
    run.runProgram(file1, inputFile, outfile1);
    run.runProgram(file2, inputFile, outfile2);

    if(compare(outfile1, outfile2) == 0)
        return 1;
    else
        return 0;
}

/*
if all number are negative, then skip.
else if all number are positive, then compare string
else return 1, dedicates m1 and m2 are not same
*/
int JudgeEqual::compare(map<int, string> &m1, map<int ,string> &m2)
{
    for(auto it1 = m1.begin(), it2 = m2.begin(); it1 != m1.end() && it2 != m2.end(); ++it1, ++it2)
    {
        if(it1->first < 0 && it2->first < 0)
            continue;
        else if(it1->first > 0 && it2->first > 0)
            if(it1->second != it2->second)
                return 1;
        else
            return 1;
    }
    return 0;
}