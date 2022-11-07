#ifndef INPUT_H
#define INPUT_H
#include <string>
<<<<<<< HEAD
using std::string;


class GenInput
{
public:
    /* Generate a single input for the program based on the input format file and return it as a string, 
    each input element is separated by a breakline*/
    string genInput(const string& inputFormatFile);    
=======
using namespace std;


class GenProgramInput
{
private:
    //Generate a random integer which is between int 'minInt' and int 'maxInt', append it to string 'target'
    void genInt(int minInt, int maxInt, string& target);
    // Generate a random letter, append it to string 'target'
    void genChar(string& target);
    // Generate a random string whose length is between length 'minLen' and length 'maxLen', append it to string "target"
    void genString(int minLen, int maxLen, string& target);
public:
    /* Generate a single input for the program based on the input format file and return it as a string,
   store the result in 'programInput'. Each input element is separated by a breakline*/
    bool genInput(const string& inputFormatFile, string& programInput);    
>>>>>>> gen-input
};


#endif