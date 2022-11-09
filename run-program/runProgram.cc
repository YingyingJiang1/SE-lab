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
    FILE* fp;
    char buf[BUF_SIZE];
    command = "for i in {1..2};do ./a.out; done </home/oslab/judge-tool/input.txt";
    fp = popen(command.c_str(), "r");
     fgets(buf, BUF_SIZE, fp);
     outputs[0] = buf;
    cout << buf << endl;
        pclose(fp);
    

  
    return true;
}

