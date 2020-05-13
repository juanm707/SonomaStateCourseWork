
CFLAGS=-std=c++11 -ggdb

OBJECTS=FCFSQueueNode.o FCFSQueue.o EventQueue.o FCFSDisk.o main.o 

fcfs_disk.x: $(OBJECTS)
	g++ $(CFLAGS) $(OBJECTS) -o fcfs_disk.x

FCFSQueueNode.o: FCFSQueueNode.cpp FCFSQueueNode.hpp
	g++ $(CFLAGS) -c FCFSQueueNode.cpp -o FCFSQueueNode.o

FCFSQueue.o: FCFSQueue.cpp FCFSQueue.hpp FCFSQueueNode.hpp 
	g++ $(CFLAGS) -c FCFSQueue.cpp -o FCFSQueue.o

EventQueue.o: EventQueue.cpp EventQueue.hpp EventNode.hpp DiskDoneEvent.hpp TimerEvent.hpp RequestEvent.hpp
	g++ $(CFLAGS) -c EventQueue.cpp -o EventQueue.o

FCFSDisk.o: FCFSDisk.cpp FCFSDisk.h FCFSQueue.hpp DiskDoneEvent.hpp RequestEvent.hpp TimerEvent.hpp
	g++ $(CFLAGS) -c FCFSDisk.cpp -o FCFSDisk.o

main.o: main.cpp FCFSQueue.hpp FCFSQueueNode.hpp
	g++ $(CFLAGS) -c main.cpp -o main.o

clean:
	rm -fr *~ $(OBJECTS) fcfs_disk.x FCFS_output.txt SUMMARY_output.txt
