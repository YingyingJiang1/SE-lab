cc = g++
objs = main.cc judgeTool.cc ./gen-input/genInput.cc ./judge-equivalence/judgeEqual.cc ./run-program/runProgram

judgeTool:
	cc -c -g $(objs) -o judgeTool
	make clean

clean:
	rm -f *.o