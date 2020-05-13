L08a.out : Lab08a.o Square.o Circle.o EquiTri.o Rectangle.o Triangle.o Shape.o
	g++ -o L08a.out Lab08a.o Square.o Circle.o EquiTri.o Rectangle.o Triangle.o Shape.o

Lab08a.o : Lab08a.cpp Square.h Circle.h EquiTri.h Rectangle.o Triangle.o Shape.h
	g++ -c Lab08a.cpp

Square.o : Square.cpp Square.h
	g++ -c Square.cpp

Circle.o : Circle.cpp Circle.h
	g++ -c Circle.cpp

EquiTri.o : EquiTri.cpp EquiTri.h
	g++ -c EquiTri.cpp

Rectangle.o : Rectangle.cpp Rectangle.h
	g++ -c Rectangle.cpp

Triangle.o : Triangle.cpp Triangle.h
	g++ -c Triangle.cpp

Shape.o : Shape.cpp Shape.h
	g++ -c Shape.cpp

L08b.out : Lab08b.o Square.o Circle.o EquiTri.o Rectangle.o Triangle.o Shape.o
	g++ -o L08b.out Lab08b.o Square.o Circle.o EquiTri.o Rectangle.o Triangle.o Shape.o

Lab08b.o : Lab08b.cpp Square.h Circle.h EquiTri.h Rectangle.h Triangle.h Shape.h
	g++ -c Lab08b.cpp

clean :
	rm -f *.o L08[ab].out
