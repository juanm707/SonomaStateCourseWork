/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#ifndef PROJECT3_EVENTQUEUE_H
#define PROJECT3_EVENTQUEUE_H

#include "EventNode.hpp"

class EventQueue {

public:

    EventQueue(): head(nullptr), tail(nullptr), numEvents(0), currentTime(0){}
    ~EventQueue();

    void addEvent ( EventNode * event);

    EventNode * popEvent (); //return the next event

    //void proccessEvent(EventNode * eventN, EventQueue * queueEvent);

    int numberOfEv () { return numEvents; }

    bool isEmpty() { return head == nullptr || numEvents == 0; }

    void setTime(int setT) { currentTime = setT; }

    int getTime() { return currentTime; }

    void printQ();


private:
    EventNode *head, *tail;
    int numEvents;
    int currentTime;

    // HELPER FUNCTIONS
    void InsertFirst (EventNode * eventN);
    void InsertLast (EventNode * eventN);

};


#endif //PROJECT3_EVENTQUEUE_H
