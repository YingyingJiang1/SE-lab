#include <iostream>
#include <fstream>
#include <sstream>
#include "genInput.h"


int GenProgramInput::genInput( int n, string& inputFile)
{
    ofstream out;
    out.open(inputFile, ios::out);
    if(!out)
    {
        cout << "Failed to open file \"" << inputFile << "\"\n";
        return 0;
    }
    
    string inputs;
    int num = 0;
    for(int i = 0; i < n; ++i)
    {
        if(genSingleInput(inputs))
        {
            ++num;
            inputs.append(1, '\n');
        }
    }

    out << inputs;
    out.close();
    return n;
}

bool GenProgramInput::genSingleInput (string& programInput)
{
    programInput.clear();
    ifstream in;
    in.open(inputFormatFile, ios::in);
    if(!in)
    {
        cout << "Fail to open file \"" << inputFormatFile << "\".\n";
        return false;
    }

    string format, type;    
    in >> format;
    while(!in.fail())
    {
        int i = format.find("(") ;
        type = format.substr(0, i);

        if(type == "char")
            genChar(programInput);
            
       else 
       {
           int i1 = format.find(",", i+1);
           int i2 = format.find(")", i1 + 1);
           int l, r;

           // get the range of int or length range of string
           stringstream ss;
           ss << format.substr(i+1, i1-i-1) << " " << format.substr(i1+1, i2-i1-1);           
           ss >> l >> r;

           if(type == "int")
                genInt(l, r, programInput);
            else if(type == "string")
                genString(l, r, programInput);
            else 
                return false;
       }
       programInput.append(1, ' ');
        in >> format;        
    }

    in.close();
    return true;

}


void GenProgramInput::genChar(string& target)
{
    // rand() % 26 + 65: generate a uppercase letter, 32 is difference between uppercase and lowercase.
    // value of rand() % 2 * 32 is either 0 or 32, if value is 32 then transform uppercase to lowercase.
    int asc = rand() % 26 + 65 + rand() % 2 * 32;
    char ch = asc;
    target.append(1, ch);
}

void GenProgramInput::genInt(int minInt, int maxInt, string& target)
{
    int m = rand() % (maxInt - minInt + 1) + minInt;
    stringstream ss;
    ss << m;
    target.append(ss.str());
}

void GenProgramInput::genString(int minLen, int maxLen, string& target)
{
    int len = rand() % (maxLen - minLen + 1) + minLen;
    for(int i = 0; i < len; ++i)
        genChar(target);
}