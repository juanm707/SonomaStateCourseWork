lab12 : Lab12app.o card.o
	g++ -o lab12 Lab12app.o card.o -g

Lab12app.o : Lab12app.cpp LList2.hpp card.h
	g++ -c Lab12app.cpp -g -w

card.o : card.cpp card.h
	g++ -c card.cpp -g

clean :
	rm -f *.o lab12
