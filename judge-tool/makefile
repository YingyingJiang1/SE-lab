cc = g++
objs =  main.o judgeTool.o judgeEqual.o   genInput.o runProgram.o
#VPATH = input:compiler:execute

judgeTool: $(objs)
	$(cc) -o  judgeTool $(objs)
	make clean

main.o:
	$(cc) -c -g main.cc
judgeTool.o: judgeTool.h
	$(cc) -c -g judgeTool.cc
judgeEqual.o:  judge-equivalence/judgeEqual.h run-program/runProgram.h
	$(cc) -c -g  judge-equivalence/judgeEqual.cc
runProgram.o: run-program/runProgram.h
	$(cc) -c -g run-program/runProgram.cc
genInput.o: gen-input/genInput.h
	$(cc) -c -g gen-input/genInput.cc

.PHONY:clean
clean:
	-rm *.o 

