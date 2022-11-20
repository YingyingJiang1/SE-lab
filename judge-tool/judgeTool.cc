#include "judgeTool.h"
#include <sstream>
#include <cstdio>
#include <fstream>
#include <iostream>
#define BUF_SIZE 0xff
using std::cout;

JudgeTool::~JudgeTool()
{
    FileDir* cur = fileDirs, *pre = cur;
   while(cur)
    {
        if(cur->cppFiles)
            delete [] cur->cppFiles;
        pre = cur;
        cur = cur->next;
        delete pre;
    }
}

JudgeTool::JudgeTool(const JudgeTool& judgeTool)
{
    cout << "copy constructor of JudgeTool was called!\n";
    abort();
}

/*
paras: ss->target stringstream, dir: path of directory
return: if error occurred then return false, else return true.
*/
bool JudgeTool::getDirContent(stringstream& ss, string& dir)
{
    // get path of all subdiretories of inputed directory
    char buf[BUF_SIZE];
    FILE*fp;
    string path;
    if(dir[dir.length()-1] != '/')
        dir.append(1, '/');
    string command = "ls " + dir + "* -d";
    fp = popen(command.c_str(), "r");
   while( fgets(buf, BUF_SIZE, fp) != 0)
        ss << buf;
    pclose(fp);

    // check whether succeed
    if(ss.str().find("ls:") <= ss.str().length())
    {
        cout << "Failed to visit subdirectories of \"" << dir << "\"\n";
        return false;
    }
    return true;
}


void JudgeTool::readInput(string& input)
{   
    stringstream ss;
    if(!getDirContent(ss, input))
        return;
   
    string path;
    // get path of all files in each subdirectory and fill in struct FileDir
    while(ss >> path)
    {
        FileDir* ptr = new FileDir;
        ptr->next = fileDirs;
        fileDirs = ptr;
        fillInFD(ptr, path);          
    }
}

/**
 * paras: ptr->point of target struct FileDir, dirPath->path of directory
 */
void JudgeTool::fillInFD(FileDir* ptr, string& dirPath)
{
    stringstream ss;
    if(!getDirContent(ss, dirPath))
    {
        cout << "Failed to visit subdirectories of \"" << dirPath << "\"\n";
        ptr->cppFiles = NULL;
        ptr->num = 0;
        return;
    }
   
    int count = 0, size = 50;
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
        cout << "Fail to open file \"" << equalRes << "\" or \"" << inequalRes << "\" for writing.\n";
        cout << "Please make sure that the output folder is included in the program working directory.\n";
        exit(0);
    }

    // determine times of execution for a single program
    int times = 250;
    string column = "file1, file2\n";
    outEqual << column;
    outInequal << column;
   for(FileDir* cur = fileDirs; cur; cur = cur->next)
    {
        if(cur->num == 0)
            continue;
        int fileNums = cur->num;
        // generate input
        string inputs;
        GenProgramInput input(cur->inputFormatFile);
        input.genInput(times, inputs);

        // run programs and get execution result of all programs
        RunProgram run(inputs, times);
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