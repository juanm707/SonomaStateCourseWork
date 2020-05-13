# makefile to create echoString3

# link object files and system libraries to create executable
echoString3: echoString3.o writeStr.o readLn.o
	gcc -o echoString3 echoString3.o writeStr.o readLn.o

# compile/assemble source files to create object files
echoString3.o: echoString3.c writeStr.h readLn.h
	gcc -g -c echoString3.c

writeStr.o: writeStr.c writeStr.h
	gcc -g -c writeStr.c

readLn.o: readLn.c readLn.h
	gcc -g -c readLn.c

#remove object files and backup files
clean:
	rm -i *.o *~
