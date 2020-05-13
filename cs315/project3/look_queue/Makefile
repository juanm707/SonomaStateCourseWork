
CFLAGS=-std=c++11 -ggdb

OBJECTS=FCFSQueueNode.o FCFSQueue.o LOOKQueueNode.o LOOKQueue.o main.o 

look_queue.x: $(OBJECTS)
	g++ $(CFLAGS) $(OBJECTS) -o look_queue.x

FCFSQueueNode.o: FCFSQueueNode.cpp FCFSQueueNode.hpp
	g++ $(CFLAGS) -c FCFSQueueNode.cpp -o FCFSQueueNode.o

FCFSQueue.o: FCFSQueue.cpp FCFSQueue.hpp FCFSQueueNode.hpp 
	g++ $(CFLAGS) -c FCFSQueue.cpp -o FCFSQueue.o

LOOKQueueNode.o: LOOKQueueNode.cpp LOOKQueueNode.hpp
	g++ $(CFLAGS) -c LOOKQueueNode.cpp -o LOOKQueueNode.o

LOOKQueue.o: LOOKQueue.cpp LOOKQueue.hpp LOOKQueueNode.hpp
	g++ $(CFLAGS) -c LOOKQueue.cpp -o LOOKQueue.o

main.o: main.cpp FCFSQueue.hpp FCFSQueueNode.hpp LOOKQueue.hpp LOOKQueueNode.hpp
	g++ $(CFLAGS) -c main.cpp -o main.o

clean:
	rm -fr *~ $(OBJECTS) look_queue.x outputFile.txt
