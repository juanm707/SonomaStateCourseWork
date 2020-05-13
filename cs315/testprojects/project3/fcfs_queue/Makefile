
CFLAGS=-std=c++11 -ggdb

OBJECTS=FCFSQueueNode.o FCFSQueue.o main.o 

fcfs_queue.x: $(OBJECTS)
	g++ $(CFLAGS) $(OBJECTS) -o fcfs_queue.x

FCFSQueueNode.o: FCFSQueueNode.cpp FCFSQueueNode.hpp
	g++ $(CFLAGS) -c FCFSQueueNode.cpp -o FCFSQueueNode.o

FCFSQueue.o: FCFSQueue.cpp FCFSQueue.hpp FCFSQueueNode.hpp 
	g++ $(CFLAGS) -c FCFSQueue.cpp -o FCFSQueue.o

main.o: main.cpp FCFSQueue.hpp FCFSQueueNode.hpp
	g++ $(CFLAGS) -c main.cpp -o main.o

clean:
	rm -fr *~ $(OBJECTS) fcfs_queue.x outputFile.txt fcfs_test.x
