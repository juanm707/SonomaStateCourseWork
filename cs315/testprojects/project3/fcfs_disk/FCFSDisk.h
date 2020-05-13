/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#ifndef PROJECT3_FCFSDISK_H
#define PROJECT3_FCFSDISK_H

#include "FCFSQueue.hpp"
#include "DiskDoneEvent.hpp"
#include "RequestEvent.hpp"
#include "TimerEvent.hpp"
#include <fstream>
#include <climits>
#include <cstdint>

class FCFSDisk {

public:

    FCFSDisk( FCFSQueue * q): waitQueue(q), _track(0), _sector(0), state(0), type("fcfs"),
                              write(0), init(0), count(0), currentDiskTime(0), numRequests(0),
                              minTS(INT_MAX), maxTS(INT_MIN), totalTS(0),
                              minWT(INT_MAX), maxWT(INT_MIN), totalWT(0),
                              minST(INT_MAX), maxST(INT_MIN), totalST(0), server(nullptr) { }

    DiskDoneEvent * proccessRequest ( RequestEvent * reqEvent, int currentT );
    DiskDoneEvent * proccessDiskDone ( DiskDoneEvent * diskDoneE, int currentT);
    void processTimerEvent (); //maybe take a timer parameter

    void printDisk();
    void printSummary();
    
private:
    FCFSQueue * waitQueue;

    Request * server;

    int _track, _sector, state, write, count, currentDiskTime,numRequests;
    double init, minTS,maxTS, totalTS,
    minWT, maxWT, totalWT,
    minST, maxST, totalST;
    std::string type;

};

#endif //PROJECT3_FCFSDISK_H
