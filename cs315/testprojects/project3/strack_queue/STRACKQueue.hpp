/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#ifndef __STRACKQueue_hpp
#define __STRACKQueue_hpp

#include<iostream>
#include "STRACKQueueNode.hpp"

class Request;

class STRACKQueue: public Queue {

public:
    STRACKQueue(): head(nullptr), tail(nullptr), currentTrack(0), currentSector(0), numReq(0), firstTime(0), completedReq(0), numTracks(0) {}

    virtual void addRequest(Request *request);
    virtual Request *getRequest();
    virtual bool isEmpty();
    bool isReallyEmpty();
    virtual void print();
    virtual ~STRACKQueue();

private:
    STRACKQueueNode *head, *tail;
    int currentTrack;
    int currentSector;
    double firstTime;
    int numReq;
    int completedReq;
    int numTracks;
};

#endif
