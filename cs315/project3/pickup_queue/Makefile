
CFLAGS=-std=c++11 -ggdb

OBJECTS=FCFSQueueNode.o FCFSQueue.o PICKUPQueueNode.o PICKUPQueue.o main.o 

pickup_queue.x: $(OBJECTS)
	g++ $(CFLAGS) $(OBJECTS) -o pickup_queue.x

FCFSQueueNode.o: FCFSQueueNode.cpp FCFSQueueNode.hpp
	g++ $(CFLAGS) -c FCFSQueueNode.cpp -o FCFSQueueNode.o

FCFSQueue.o: FCFSQueue.cpp FCFSQueue.hpp FCFSQueueNode.hpp 
	g++ $(CFLAGS) -c FCFSQueue.cpp -o FCFSQueue.o

PICKUPQueueNode.o: PICKUPQueueNode.cpp PICKUPQueueNode.hpp
	g++ $(CFLAGS) -c PICKUPQueueNode.cpp -o PICKUPQueueNode.o

PICKUPQueue.o: PICKUPQueue.cpp PICKUPQueue.hpp PICKUPQueueNode.hpp
	g++ $(CFLAGS) -c PICKUPQueue.cpp -o PICKUPQueue.o

main.o: main.cpp FCFSQueue.hpp FCFSQueueNode.hpp PICKUPQueue.hpp PICKUPQueueNode.hpp
	g++ $(CFLAGS) -c main.cpp -o main.o

clean:
	rm -fr *~ $(OBJECTS) pickup_queue.x outputFile.txt
