/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#ifndef __CLOOKQueue_hpp
#define __CLOOKQueue_hpp

#include<iostream>

#include "CLOOKQueueNode.hpp"

class Request;

class CLOOKQueue: public Queue {

public:
    CLOOKQueue(): head(nullptr), tail(nullptr), firstNode(nullptr), currentTrack(0), currentSector(0), numReq(0), firstTime(0), completedReq(0), firstTrack(0) {}

    virtual void addRequest(Request *request);
    virtual Request *getRequest();
    virtual bool isEmpty();
    virtual void print();
    virtual ~CLOOKQueue();

private:
    CLOOKQueueNode *head, *tail, *firstNode;
    int currentTrack;
    int currentSector;
    double firstTime;
    int firstTrack;
    int numReq;
    int completedReq;

    //helper functions
    void InsertFirst (Request * request);
    void InsertLast (Request * request);
    bool DeleteFirst ();
    bool DeleteLast ();
    bool Delete (int trackToDelete);
};

#endif
