P2.out: Proj2app.o SetLimits.o CLife.o
	g++ -g -o P2.out Proj2app.o SetLimits.o CLife.o

Proj2app.o: Proj2app.cpp SetLimits.h CLife.h
	g++ -g -c Proj2app.cpp

SetLimits.o: SetLimits.cpp SetLimits.h
	g++ -g -c SetLimits.cpp

CLife.o: CLife.cpp CLife.h
	g++ -g -c CLife.cpp

clean:
	rm *.o P2.out

run : P2.out
	clear
	./P2.out

submit : Proj2app.cpp CLife.h CLife.cpp makefile README.txt
	rm -rf martinezP2
	mkdir martinezP2
	cp Proj2app.cpp martinezP2
	cp CLife.h martinezP2
	cp CLife.cpp martinezP2
	cp makefile martinezP2
	cp README.txt martinezP2
	tar cfvz martinezP2.tgz martinezP2
	cp martinezP2.tgz ~tiawatts/cs215drop
