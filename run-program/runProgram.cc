#include <cstdio>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string.h>
#include "runProgram.h"
using std::cin;
using std::cout;
#define BUF_SIZE 0xffff
bool  RunProgram::runProgram(string& cppFile, map<int, string>& outputs)
{
    // Redirect standard input to a file
    ifstream fin(inputFile);
    if(!fin)
    {
        cout << "Failed to open \"" << inputFile << "\"\n";
        return false;
    }
    streambuf* oldcin = cin.rdbuf(fin.rdbuf());

    if(!compile(cppFile))
        return false;

    execution(n, outputs, fin);

    cin.rdbuf(oldcin);
    fin.close();
}


// compile cppFile, if failed then return false
inline bool RunProgram::compile(string& cppFile)
{
    // compile cppFile
    string command = "g++ -w " + cppFile;    
    FILE* fp = popen(command.c_str(), "r");
    if(fgetc(fp) != EOF)
    {
        cout << "Failed to compile \"" << cppFile << "\"\n";
        return false;
    }
    pclose(fp);
    return true;
}

// run cppFile n times and store the result of every execution in outputs
inline void RunProgram::execution(int n, map<int, string>& outputs, ifstream& fin)
{
    string command;
    FILE* fp;
    char buf[BUF_SIZE];
    command = " timeout 2s ./a.out";
    for(int i = 1; i <= n; ++i)
    {
        fp = popen(command.c_str(), "r");
        if(!fp)
            outputs[-i] = "";
        else
        {
            fgets(buf, BUF_SIZE, fp);
            outputs[i] = buf;
        }
        pclose(fp);
    }
}

