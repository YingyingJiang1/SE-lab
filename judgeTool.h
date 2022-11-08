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

    // get contents of dirPath and fill in memory which is pointed by ptr
   void fillInFD(FileDir* ptr, string& dirPath);

   // get contents of directory dir (not recursion) and puts the contents to stringstream ss
   bool getDirContent(stringstream& ss, string& dir);

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

