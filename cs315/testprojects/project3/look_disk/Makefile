
CFLAGS=-std=c++11 -ggdb

OBJECTS=FCFSQueueNode.o FCFSQueue.o LOOKQueueNode.o LOOKQueue.o EventQueue.o LOOKDisk.o main.o 

look_disk.x: $(OBJECTS)
	g++ $(CFLAGS) $(OBJECTS) -o look_disk.x

FCFSQueueNode.o: FCFSQueueNode.cpp FCFSQueueNode.hpp
	g++ $(CFLAGS) -c FCFSQueueNode.cpp -o FCFSQueueNode.o

FCFSQueue.o: FCFSQueue.cpp FCFSQueue.hpp FCFSQueueNode.hpp 
	g++ $(CFLAGS) -c FCFSQueue.cpp -o FCFSQueue.o

LOOKQueueNode.o: LOOKQueueNode.cpp LOOKQueueNode.hpp
	g++ $(CFLAGS) -c LOOKQueueNode.cpp -o LOOKQueueNode.o

LOOKQueue.o: LOOKQueue.cpp LOOKQueue.hpp LOOKQueueNode.hpp
	g++ $(CFLAGS) -c LOOKQueue.cpp -o LOOKQueue.o

EventQueue.o: EventQueue.cpp EventQueue.hpp EventNode.hpp DiskDoneEvent.hpp TimerEvent.hpp RequestEvent.hpp
	g++ $(CFLAGS) -c EventQueue.cpp -o EventQueue.o

LOOKDisk.o: LOOKDisk.cpp LOOKDisk.h DiskDoneEvent.hpp RequestEvent.hpp TimerEvent.hpp
	g++ $(CFLAGS) -c LOOKDisk.cpp -o LOOKDisk.o

main.o: main.cpp FCFSQueue.hpp FCFSQueueNode.hpp LOOKQueue.hpp LOOKQueueNode.hpp LOOKDisk.h LOOKDisk.cpp
	g++ $(CFLAGS) -c main.cpp -o main.o

clean:
	rm -fr *~ $(OBJECTS) look_disk.x LOOK_output.txt LOOK_summary.txt
