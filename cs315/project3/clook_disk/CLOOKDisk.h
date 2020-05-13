/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 3
*/

#ifndef PROJECT3_CLOOKDISK_H
#define PROJECT3_CLOOKDISK_H

#include "CLOOKQueue.hpp"
#include "DiskDoneEvent.hpp"
#include "RequestEvent.hpp"
#include "TimerEvent.hpp"
#include <climits>

class CLOOKDisk {

public:

    CLOOKDisk( CLOOKQueue * q): waitQueue(q), _track(0), _sector(0), state(0), write(0), count(0), init(0), type("clook"),
    minTS(INT_MAX), maxTS(INT_MIN), totalTS(0),
    minWT(INT_MAX), maxWT(INT_MIN), totalWT(0),
    minST(INT_MAX), maxST(INT_MIN), totalST(0), server(nullptr) {}

    DiskDoneEvent * proccessRequest ( RequestEvent * reqEvent, int currentT );
    DiskDoneEvent * proccessDiskDone ( DiskDoneEvent * diskDoneE, int currentT);
    void processTimerEvent (); //maybe take a timer parameter

    void printDisk();
    void printSummary();

private:
    CLOOKQueue * waitQueue;

    Request * server;

    int _track, _sector, state, write, count;
    double init, minTS,maxTS, totalTS,
      minWT, maxWT, totalWT,
      minST, maxST, totalST;
    std::string type;

};


#endif //PROJECT3_CLOOKKDISK_H
