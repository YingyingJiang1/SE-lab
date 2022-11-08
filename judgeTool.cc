#include "judgeTool.h"
#include <sstream>
#include <cstdio>
#include <fstream>
#include <iostream>
#define MAX_INT 0x7fffffff
using std::cout;

JudgeTool::~JudgeTool()
{
    FileDir* cur = fileDirs;
   while(cur)
    {
        if(cur->cppFiles)
            delete cur->cppFiles;
        cur = cur->next;
    }
    delete fileDirs;
}

/* */
JudgeTool::JudgeTool(const JudgeTool& judgeTool)
{
    cout << "copy constructor of JudgeTool was called!\n";
    abort();
}


void JudgeTool::readInput()
{
    string input;
    cin >> input;

    // get path of all subdiretories of inputed directory
    FILE*fp;
    stringstream ss;
    string path;
    if(input[input.length()-1] != '/')
        input.append(1, '/');
    string command = "ls " + input + "* -d";
    FILE* fp = popen(command.c_str(), "r");
    if(!fp)
    {
        cout << "Failed to ls subdirectories of \"" << input << "\"\n";
        return;
    }
    pclose(fp);

    // get path of all files in each subdirectory
    stringstream  ss1;
    ss << fp;
    while(ss >> path)
    {
        FileDir* ptr = new FileDir;
        ptr->next = fileDirs;
        fileDirs = ptr;
        fillInFD(ptr, path);               
        pclose(fp);
    }

}

void JudgeTool::fillInFD(FileDir* ptr, const string& dirPath)
{
    int count = 0, size = 50;
    string command = "ls " + dirPath + "/* -d";
    string filePath;
    FILE* fp = popen(command.c_str(), "r");
    stringstream ss;
    ss << fp;
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

    FileDir* cur = fileDirs;
    while(cur)
    {
        int fileNums = cur->num;
        for(int j =0; j < fileNums; ++j)
        {
            for(int k = j +1 ; k < fileNums; ++k)
            {
                if(judge.judgeEquivalence(cur->cppFiles[j], cur->cppFiles[k], cur->inputFormatFile))
                    outEqual << cur->cppFiles[j] << "," <<cur->cppFiles[k] << "\n";
                else
                    outInequal << cur->cppFiles[j] << "," << cur->cppFiles[k] << "\n";
            }
        }
        cur = cur->next;
    }

    outEqual.close();
    outInequal.close();
}