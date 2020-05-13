
CFLAGS=-std=c++11 -ggdb

OBJECTS=FCFSQueueNode.o FCFSQueue.o STRACKQueueNode.o STRACKQueue.o main.o 

strack_queue.x: $(OBJECTS)
	g++ $(CFLAGS) $(OBJECTS) -o strack_queue.x

FCFSQueueNode.o: FCFSQueueNode.cpp FCFSQueueNode.hpp
	g++ $(CFLAGS) -c FCFSQueueNode.cpp -o FCFSQueueNode.o

FCFSQueue.o: FCFSQueue.cpp FCFSQueue.hpp FCFSQueueNode.hpp 
	g++ $(CFLAGS) -c FCFSQueue.cpp -o FCFSQueue.o

STRACKQueueNode.o: STRACKQueueNode.cpp STRACKQueueNode.hpp
	g++ $(CFLAGS) -c STRACKQueueNode.cpp -o STRACKQueueNode.o

STRACKQueue.o: STRACKQueue.cpp STRACKQueue.hpp STRACKQueueNode.hpp
	g++ $(CFLAGS) -c STRACKQueue.cpp -o STRACKQueue.o

main.o: main.cpp FCFSQueue.hpp FCFSQueueNode.hpp STRACKQueue.hpp STRACKQueueNode.hpp
	g++ $(CFLAGS) -c main.cpp -o main.o

clean:
	rm -fr *~ $(OBJECTS) strack_queue.x outputFile.txt
