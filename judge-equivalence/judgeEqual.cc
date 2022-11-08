#include "judgeEqual.h"
#include <iostream>
/*
if all number are negative, then skip.
else if all number are positive, then compare string
else return 0, dedicates m1 and m2 are not same
*/
int JudgeEqual::equivalence(map<int, string> &m1, map<int ,string> &m2)
{
    if(m1.empty() || m2.empty())
        return 0;
    for(auto it1 = m1.begin(), it2 = m2.begin(); it1 != m1.end() && it2 != m2.end(); ++it1, ++it2)
    {
        if(it1->first < 0 && it2->first < 0)
            continue;
        else if(it1->first > 0 && it2->first > 0)
        {
            if(it1->second != it2->second)
                return 0;
        }            
        else
            return 0;
    }
    return 1;
}