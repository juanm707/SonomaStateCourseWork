
CFLAGS= -std=c++11

binTree.x: BinSearchTree.o main.o
	g++ $(CFLAGS) -o binTree.x BinSearchTree.o main.o

BinSearchTree.o: TreeNode.hpp BinSearchTree.hpp BinSearchTree.cpp
	g++ $(CFLAGS) -c -o BinSearchTree.o BinSearchTree.cpp

main.o: BinSearchTree.hpp TreeNode.hpp main.cpp
	g++ $(CFLAGS) -c -o main.o main.cpp

clean:
	rm -f *.o *.x *~
