
CFLAGS=-std=c++11 -ggdb

OBJECTS=FCFSQueueNode.o FCFSQueue.o CLOOKQueueNode.o CLOOKQueue.o EventQueue.o CLOOKDisk.o main.o 

clook_disk.x: $(OBJECTS)
	g++ $(CFLAGS) $(OBJECTS) -o clook_disk.x

FCFSQueueNode.o: FCFSQueueNode.cpp FCFSQueueNode.hpp
	g++ $(CFLAGS) -c FCFSQueueNode.cpp -o FCFSQueueNode.o

FCFSQueue.o: FCFSQueue.cpp FCFSQueue.hpp FCFSQueueNode.hpp 
	g++ $(CFLAGS) -c FCFSQueue.cpp -o FCFSQueue.o

CLOOKQueueNode.o: CLOOKQueueNode.cpp CLOOKQueueNode.hpp
	g++ $(CFLAGS) -c CLOOKQueueNode.cpp -o CLOOKQueueNode.o

CLOOKQueue.o: CLOOKQueue.cpp CLOOKQueue.hpp CLOOKQueueNode.hpp
	g++ $(CFLAGS) -c CLOOKQueue.cpp -o CLOOKQueue.o

EventQueue.o: EventQueue.cpp EventQueue.hpp EventNode.hpp DiskDoneEvent.hpp TimerEvent.hpp RequestEvent.hpp
	g++ $(CFLAGS) -c EventQueue.cpp -o EventQueue.o

CLOOKDisk.o: CLOOKDisk.cpp CLOOKDisk.h DiskDoneEvent.hpp RequestEvent.hpp TimerEvent.hpp
	g++ $(CFLAGS) -c CLOOKDisk.cpp -o CLOOKDisk.o

main.o: main.cpp FCFSQueue.hpp FCFSQueueNode.hpp CLOOKQueue.hpp CLOOKQueueNode.hpp CLOOKDisk.h CLOOKDisk.cpp
	g++ $(CFLAGS) -c main.cpp -o main.o

clean:
	rm -fr *~ $(OBJECTS) clook_disk.x CLOOK_output.txt CLOOK_summary.txt
