L10.out : Lab10app.o LList.o
	g++ -o L10.out Lab10app.o LList.o -g

Lab10app.o : Lab10app.cpp LList.h
	g++ -c Lab10app.cpp -g

LList.o : LList.cpp LList.h
	g++ -c LList.cpp -g

clean :
	rm -f *.o L10.out

