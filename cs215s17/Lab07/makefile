L07a.out : Lab07a.o CoordPt.o
	g++ -o L07a.out Lab07a.o CoordPt.o

Lab07a.o : Lab07a.cpp CoordPt.h
	g++ -c Lab07a.cpp -g

CoordPt.o : CoordPt.cpp CoordPt.h
	g++ -c CoordPt.cpp -DDEBUG

runA : L07a.out points.txt
	./L07a.out points.txt

L07d.out : Lab07a.o CoordPtD.o
	g++ -o L07d.out Lab07a.o CoordPtD.o

CoordPtD.o : CoordPt.cpp CoordPt.h
	g++ -c CoordPt.cpp -o CoordPtD.o -g -DDEBUG

runD : L07d.out points.txt
	./L07d.out points.txt

L07b.out : Lab07b.o WordData.o
	g++ -o L07b.out Lab07b.o WordData.o

Lab07b.o : Lab07b.cpp WordData.h
	g++ -c Lab07b.cpp -g

WordData.o : WordData.cpp WordData.h
	g++ -c WordData.cpp -g

runB : L07b.out words.txt
	./L07b.out words.txt

clean :
	rm -f *.o L07*.out
