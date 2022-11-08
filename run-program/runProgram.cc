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

    // compile cppFile
    string command = "g++ -w " + cppFile;    
    FILE* fp = popen(command.c_str(), "r");
    if(fgetc(fp) != EOF)
    {
        cout << "Failed to compile \"" << cppFile << "\"\n";
        return false;
    }
    pclose(fp);
    // run cppFile and store the result of every execution
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

    cin.rdbuf(oldcin);
    fin.close();
}