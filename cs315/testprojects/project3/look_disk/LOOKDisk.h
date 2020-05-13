/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#ifndef PROJECT3_LOOKDISK_H
#define PROJECT3_LOOKDISK_H

#include "LOOKQueue.hpp"
#include "DiskDoneEvent.hpp"
#include "RequestEvent.hpp"
#include "TimerEvent.hpp"
#include <climits>

class LOOKDisk {

public:

    LOOKDisk( LOOKQueue * q): waitQueue(q), _track(0), _sector(0), state(0), write(0), count(0), init(0), type("look"),
    minTS(INT_MAX), maxTS(INT_MIN), totalTS(0),
    minWT(INT_MAX), maxWT(INT_MIN), totalWT(0),
    minST(INT_MAX), maxST(INT_MIN), totalST(0),server(nullptr) {}

    DiskDoneEvent * proccessRequest ( RequestEvent * reqEvent, int currentT );
    DiskDoneEvent * proccessDiskDone ( DiskDoneEvent * diskDoneE, int currentT);
    void processTimerEvent (); //maybe take a timer parameter

    void printDisk();
    void printSummary();

private:
    LOOKQueue * waitQueue;

    Request * server;

    int _track, _sector, state, write, count;
    double init, minTS, maxTS, totalTS,
      minWT, maxWT, totalWT,
      minST, maxST, totalST;
    std::string type;

};


#endif //PROJECT3_LOOKKDISK_H
