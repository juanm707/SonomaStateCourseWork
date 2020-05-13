
CFLAGS=-std=c++11 -ggdb

OBJECTS=FCFSQueueNode.o FCFSQueue.o CLOOKQueueNode.o CLOOKQueue.o main.o 

clook_queue.x: $(OBJECTS)
	g++ $(CFLAGS) $(OBJECTS) -o clook_queue.x

FCFSQueueNode.o: FCFSQueueNode.cpp FCFSQueueNode.hpp
	g++ $(CFLAGS) -c FCFSQueueNode.cpp -o FCFSQueueNode.o

FCFSQueue.o: FCFSQueue.cpp FCFSQueue.hpp FCFSQueueNode.hpp 
	g++ $(CFLAGS) -c FCFSQueue.cpp -o FCFSQueue.o

CLOOKQueueNode.o: CLOOKQueueNode.cpp CLOOKQueueNode.hpp
	g++ $(CFLAGS) -c CLOOKQueueNode.cpp -o CLOOKQueueNode.o

CLOOKQueue.o: CLOOKQueue.cpp CLOOKQueue.hpp CLOOKQueueNode.hpp
	g++ $(CFLAGS) -c CLOOKQueue.cpp -o CLOOKQueue.o

main.o: main.cpp FCFSQueue.hpp FCFSQueueNode.hpp CLOOKQueue.hpp CLOOKQueueNode.hpp
	g++ $(CFLAGS) -c main.cpp -o main.o

clean:
	rm -fr *~ $(OBJECTS) clook_queue.x outputFile.txt
