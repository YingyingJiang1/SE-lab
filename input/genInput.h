#ifndef INPUT_H
#define INPUT_H
#include <string>
using std::string;


class GenInput
{
public:
    /* Generate a single input for the program based on the input format file and return it as a string, 
    each input element is separated by a breakline*/
    string genInput(const string& inputFormatFile);    
};


#endif