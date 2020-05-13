/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#ifndef __EventNode_hpp
#define __EventNode_hpp

#include "TimerEvent.hpp"
#include "RequestEvent.hpp"
#include "DiskDoneEvent.hpp"
#include "Request.hpp"


class EventNode {
public:
    EventNode(): timerEvent(nullptr), requestEvent(nullptr), ddoneEvent(nullptr),
                 isTimer(false), isRequest(false), isDDone(false), _next(nullptr), _prev(nullptr), number(0) {}

    void addTimer(TimerEvent *timer) {
        timerEvent = timer;
        isTimer = true;
        number = timer->getTime();
    }

    void addRequest(RequestEvent *request) {
        requestEvent = request;
        isRequest = true;
        number = request->getReq()->time();
    }

    void addDiskDone(DiskDoneEvent *dDone) {
        ddoneEvent = dDone;
        isDDone = true;
        number = dDone->getTime();
    }

    TimerEvent *getTimer() { return timerEvent; }
    RequestEvent *getRequest() { return requestEvent; }
    DiskDoneEvent *getDiskDone() { return ddoneEvent; }

    bool isTimerEvent()    { return isTimer; }
    bool isRequestEvent()  { return isRequest; }
    bool isDiskDoneEvent() { return isDDone; }

    void next( EventNode * nextNode) { _next = nextNode;}
    void prev( EventNode * prevNode) { _prev = prevNode;}

    EventNode * next() { return _next;}
    EventNode * prev() { return _prev;}

    double getNum() { return number; }

private:
    TimerEvent *timerEvent;
    RequestEvent *requestEvent;
    DiskDoneEvent *ddoneEvent;

    EventNode *_next, *_prev;
    bool isTimer, isRequest, isDDone;

    double number; //stores the milliseconds
};

#endif
