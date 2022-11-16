# SE-lab
Implement a program equivalence judgment tool and confirmation tool.

input of judgement tool: input a folder containing multiple subfolders, each subfolder contains one or more OJ source programs written in C/C++ and a file describing the OJ input format.
input
  |__dir
      |__oj1.cpp
      |__oj2.cpp
      |__...
      |__stdin_format.txt
  |__...
  
 
output of judgement tool: a folder containing equal.csv and inequal.csv. equal.csv saves relative path pairs of equivalent OJ programs, and inequal.csv saves relative path pairs of unequal OJ programs.
output
  |___equal.csv
  |___inequal.csv
 

