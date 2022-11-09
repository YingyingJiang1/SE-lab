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
   
    if(!compile(cppFile))
        return false;

    if(!execution(n, outputs))
        return false;
    return true;
    
}


// compile cppFile, if failed then return false
 bool RunProgram::compile(string& cppFile)
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
bool RunProgram::execution(int n, map<int, string>& outputs)
{
    string command;
    string input;
    FILE* fp;
    char buf[BUF_SIZE];
    command = "timeout 2s ./a.out <input.txt 2>&1";
   int l = 0, r;
    for(int i = 1; i <= n; ++i)
    {
        r = inputs.find('\n', l);
        input = inputs.substr(l, r);
        l = r+1;
        ofstream outf;
        outf.open("input.txt", ios::out);
        outf << input;
        outf.close();
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
    return true;
}

