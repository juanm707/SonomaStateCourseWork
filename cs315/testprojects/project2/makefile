.SUFFIXES: .cpp .o

OBJS = parser.o lex.o reclists.o solutions.o main.cpp 

reclists.x:  $(OBJS)
	g++ -ggdb -o reclists.x $(OBJS)

.cpp.o:
	g++ -Wall -c -ggdb $< -o $@

parser.o: parser.cpp lex.hpp reclists.hpp
lex.o: lex.cpp lex.hpp
reclists.o: reclists.hpp reclists.cpp
solutions.o: reclists.hpp solutions.hpp solutions.cpp 
main.o: main.cpp reclists.hpp

run: reclists.x
	./reclists.x

clean:
	rm -f *.o *.x *~
