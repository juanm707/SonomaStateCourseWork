L11.out : Lab11app.o Fraction.o
	g++ -o L11.out Lab11app.o Fraction.o -g

Lab11app.o : Lab11app.cpp LList2.hpp Fraction.h
	g++ -c Lab11app.cpp -g

Fraction.o : Fraction.cpp Fraction.h
	g++ -c Fraction.cpp -g

clean :
	rm -f core.* *.o L11.out

