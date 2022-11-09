#include "judgeTool.h"
#include <iostream>
extern int no;
int main(int argc, char* argv[])
{
    string input;
    if(argc == 2)
        input = argv[argc-1];
    else
    {
        std::cout << "main need an argument: path of a directory." << std::endl;
        return 0;
    }
    JudgeTool judgeTool;
    judgeTool.readInput(input);
    judgeTool.getRes();
}

