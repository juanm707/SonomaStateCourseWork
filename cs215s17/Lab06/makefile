L06.out : Lab06.o Lab06app.o
	g++ -o L06.out Lab06.o Lab06app.o

Lab06.o : Lab06.h Lab06.cpp
	g++ -g -c Lab06.cpp

Lab06app.o : Lab06.h Lab06app.cpp
	g++ -g -c Lab06app.cpp

clean :
	rm *.o L06.out
