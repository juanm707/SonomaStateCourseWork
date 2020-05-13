/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#ifndef __FCFSQueue_hpp
#define __FCFSQueue_hpp

#include<iostream>
#include "Queue.hpp"
#include "FCFSQueueNode.hpp"

class Request;

class FCFSQueue: public Queue {

public:
    FCFSQueue(): head(nullptr), tail(nullptr), start(nullptr), currentTrack(0), currentSector(0), numReq(0), firstTime(0) {}

    virtual void addRequest(Request *request);
    virtual Request *getRequest();
    Request * getCopyRequest();
    virtual bool isEmpty();
    virtual void print(); 
    virtual ~FCFSQueue();

private:
    FCFSQueueNode *head, *tail, *start;
    int currentTrack;
    int currentSector;
    double firstTime;
    int numReq;
};

#endif
