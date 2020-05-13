
CFLAGS=-std=c++11 -Wall

infixToPostfix.x: InfixToPostfix.o Token.o TokenIterator.o main.o Number.o Tokenizer.o
	g++ $(CFLAGS) InfixToPostfix.o Token.o TokenIterator.o main.o Number.o Tokenizer.o -o infixToPostfix.x

InfixToPostfix.o: InfixToPostfix.hpp InfixToPostfix.cpp TokenIterator.hpp Token.hpp
	g++ $(CFLAGS) InfixToPostfix.cpp -o InfixToPostfix.o -c

TokenIterator.o: TokenIterator.hpp TokenIterator.cpp Token.hpp
	g++ $(CFLAGS) TokenIterator.cpp -o TokenIterator.o -c

Token.o: Token.hpp Token.cpp
	g++ $(CFLAGS) Token.cpp -o Token.o -c

main.o: main.cpp Token.hpp InfixToPostfix.hpp TokenIterator.hpp Number.cpp Tokenizer.cpp
	g++ $(CFLAGS) main.cpp -o main.o -c

Number.o: Number.h Number.cpp
	g++ $(CFLAGS) Number.cpp -o Number.o -c

Tokenizer.o: Tokenizer.cpp Tokenizer.h
	g++ $(CFLAGS) Tokenizer.cpp -o Tokenizer.o -c

run: infixToPostfix.x
	./infixToPostfix.x

clean:
	rm -f *.o *~ *.x
