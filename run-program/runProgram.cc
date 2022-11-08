#include <cstdio>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string.h>
#include "runProgram.h"
using std::cin;
using std::cout;
#define MAX_INT 0x7fffffff

bool  runProgram(string& cppFile, string& inputFile, map<int, string>& outputs, int n)
{
    // Redirect standard input to a file
    ifstream fin(inputFile);
    if(!fin)
    {
        cout << "Failed to open \"" << inputFile << "\"\n";
        return false;
    }
    streambuf* oldcin = cin.rdbuf(fin.rdbuf());

    // compile cppFile
    string command = "gcc " + cppFile;    
    FILE* fp = popen(command.c_str(), "r");
    if(!fp)
    {
        cout << "Failed to compile \"" << cppFile << "\"\n";
        return false;
    }
    pclose(fp);
    // run cppFile and store the result of every execution
    command = "./a.out";
    for(int i = 1; i <= n; ++i)
    {
       fp = popen(command.c_str(), "r");
        if(!fp)
            outputs[-i] = "";
        else
        {
            fgets((char*)outputs[i].c_str(), MAX_INT, fp);
        }
        pclose(fp);
    }

    cin.rdbuf(oldcin);
    fin.close();
}