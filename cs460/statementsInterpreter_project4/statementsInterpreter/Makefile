.SUFFIXES: .o .cpp .x

CFLAGS = -ggdb -std=c++17
objects =  Token.o Tokenizer.o Parser.o ArithExpr.o SymTab.o Statements.o TypeDescriptor.o Range.o main.o

statement.x: $(objects)
	g++ $(CFLAGS) -o statement.x $(objects)

.cpp.o:
	g++ $(CFLAGS) -c $< -o $@


Token.o:  Token.cpp Token.hpp
Tokenizer.o: Tokenizer.cpp Tokenizer.hpp
ArithExpr.o: ArithExpr.cpp ArithExpr.hpp Token.hpp SymTab.hpp
SymTab.o: SymTab.cpp SymTab.hpp
Parser.o: Parser.cpp Token.hpp Parser.hpp Tokenizer.hpp SymTab.hpp ArithExpr.hpp Statements.hpp
Statements.o: Statements.cpp Statements.hpp ArithExpr.hpp Token.hpp SymTab.hpp
TypeDescriptor.o: TypeDescriptor.cpp TypeDescriptor.hpp
Range.o: Range.cpp Range.hpp
main.o: main.cpp Token.hpp Tokenizer.hpp Parser.hpp SymTab.hpp ArithExpr.hpp Statements.hpp

clean:
	rm -fr *.o *~ *.x
