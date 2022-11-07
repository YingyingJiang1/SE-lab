#include "judgeTool.h"
#include <fstream>

JudgeTool::~JudgeTool()
{
    for(int i = 0;  i < num; ++i)
    {
        if(fileDirs[i].cppFiles)
            delete fileDirs[i].cppFiles;
    }
    delete fileDirs;
}

JudgeTool::JudgeTool(const JudgeTool& judgeTool)
{

}


void JudgeTool::readInput()
{

}


/*
paras of this method are filenames of two files
*/
void JudgeTool::getRes(string equalRes, string inequalRes)
{
    ofstream outEqual, outInequal;
    outEqual.open(equalRes, ios::out);
    outInequal.open(inequalRes, ios::out);
    if(!outEqual || !outInequal)
    {
        abort();
    }

    for(int i = 0; i < num; ++i)
    {
        int fileNums = fileDirs[i].num;
        for(int j =0; j < fileNums; ++j)
        {
            for(int k = j +1 ; k < fileNums; ++k)
            {
                if(judge.judgeEquivalence(fileDirs[i].cppFiles[j], fileDirs[i].cppFiles[k], fileDirs[i].inputFormatFile))
                    outEqual << fileDirs[i].cppFiles[j] << "," << fileDirs[i].cppFiles[k] << "\n";
                else
                    outInequal << fileDirs[i].cppFiles[j] << "," << fileDirs[i].cppFiles[k] << "\n";
            }
        }
    }

    outEqual.close();
    outInequal.close();
}