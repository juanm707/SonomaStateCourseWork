CFLAGS= -std=c++11

invertedListApp.x: main.o InvertedList.o
	g++ $(CFLAGS) -o invertedListApp.x main.o InvertedList.o

InvertedList.o: InvertedList.hpp InvertedList.cpp
	g++ $(CFLAGS) -c -o InvertedList.o InvertedList.cpp

main.o: InvertedList.hpp main.cpp
	g++ $(CFLAGS) -c -o main.o main.cpp

clean:
	rm -f *.o *.x *~

run:
	./invertedListApp.x
