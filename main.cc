#include "judgeTool.h"
#include <iostream>

int main(int argc, char* argv[])
{
    string input;
    if(argc == 2)
        input = argv[argc-1];
    else
        std::cout << "main need a argument" << std::endl;
    JudgeTool judgeTool;
    judgeTool.readInput(input);
    judgeTool.getRes();
}

