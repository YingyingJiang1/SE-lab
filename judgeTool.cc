#include "judgeTool.h"
#include <sstream>
#include <cstdio>
#include <fstream>
#include <iostream>
#define BUF_SIZE 0xff
using std::cout;

JudgeTool::~JudgeTool()
{
    FileDir* cur = fileDirs;
   while(cur)
    {
        if(cur->cppFiles)
            delete [] cur->cppFiles;
        cur = cur->next;
    }
    delete [] fileDirs;
}

/* */
JudgeTool::JudgeTool(const JudgeTool& judgeTool)
{
    cout << "copy constructor of JudgeTool was called!\n";
    abort();
}


void JudgeTool::readInput(string& input)
{   
    // get path of all subdiretories of inputed directory
    char buf[BUF_SIZE];
    FILE*fp;
    stringstream ss;
    string path;
    if(input[input.length()-1] != '/')
        input.append(1, '/');
    string command = "ls " + input + "* -d";
    fp = popen(command.c_str(), "r");
   while( fgets(buf, BUF_SIZE, fp) != 0)
        ss << buf;
   
    if(ss.str().find("ls:") <= ss.str().length())
    {
        cout << "Failed to visit subdirectories of \"" << input << "\"\n";
        return;
    }
    pclose(fp);

    // get path of all files in each subdirectory
    stringstream  ss1;
    while(ss >> path)
    {
        FileDir* ptr = new FileDir;
        ptr->next = fileDirs;
        fileDirs = ptr;
        fillInFD(ptr, path);          
    }
}

void JudgeTool::fillInFD(FileDir* ptr, const string& dirPath)
{
    char buf[BUF_SIZE];
    int count = 0, size = 50;
    string command = "ls " + dirPath + "/* -d";
    string filePath;
    stringstream ss;
    FILE* fp = popen(command.c_str(), "r");
    while(fgets(buf, BUF_SIZE, fp))
        ss << buf;
    if(ss.str().find("ls:") <= ss.str().length())
    {
        cout << "Failed to visit subdirectories of \"" << dirPath << "\"\n";
        ptr->cppFiles = NULL;
        ptr->num = 0;
        return;
    }
    ptr->cppFiles = new string[size];

    L:
    while(count < size && ss >> ptr->cppFiles[count])
        ++count;
    // string array overflow
    if(count == size)
    {           
        size *= 2;
        string* newArr = new string[size];
        for(int i = 0; i < count; ++i)
        {
            newArr[i] = ptr->cppFiles[i];            
        }
        ptr->cppFiles = newArr;
        goto L;
    }

    // last file is input format file
    ptr->inputFormatFile = ptr->cppFiles[count-1];
    ptr->num = count-1;
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
   for(FileDir* cur = fileDirs; cur; cur = cur->next)
    {
        if(cur->num == 0)
            continue;
        int fileNums = cur->num;
        // generate input
        string inputFile;
        GenProgramInput input(cur->inputFormatFile);
        input.genInput(1, inputFile);

        // run programs and get execution result of all program
        RunProgram run(inputFile);
        map<int, string>* outputs = new map<int, string>[fileNums];
        for(int i = 0; i < fileNums; ++i)
            run.runProgram( cur->cppFiles[i], outputs[i]);

        // determine the equivalence of program pairs
        for(int j =0; j < fileNums; ++j)
        {
            for(int k = j +1 ; k < fileNums; ++k)
            {
                if(judge.equivalence(outputs[j], outputs[k]))
                    outEqual << cur->cppFiles[j] << "," <<cur->cppFiles[k] << "\n";
                else
                    outInequal << cur->cppFiles[j] << "," << cur->cppFiles[k] << "\n";
            }
        }
        delete [] outputs;
    }

    outEqual.close();
    outInequal.close();
}