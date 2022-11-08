#ifndef JUDGE_TOOL
#define JUDGE_TOOL
#include "judge-equivalence/judgeEqual.h"
#include <string>
using std::string;

typedef struct FileDir
{
    string * cppFiles;
    string inputFormatFile;    
    int num;    // the number of cpp files
    struct FileDir* next;
}FileDir;

class JudgeTool
{
private:
    JudgeEqual judge;
    FileDir* fileDirs;
   // int num;
   void fillInFD(FileDir* ptr, const string& dirPath);
public:
    JudgeTool(){fileDirs = NULL;};
    ~JudgeTool();
    JudgeTool(const JudgeTool& judgeTool);
    // read and parsing user input to assign values to data members of JudgeTool
    void readInput(string& input);
    //Write filenames of all equivalent program pairs  to file 'equalRes' and all inequivalent program pairs  to file 'inequalRes'
    void getRes(string equalRes = "equal.csv", string inequalRes = "inequal.csv");
};


#endif

