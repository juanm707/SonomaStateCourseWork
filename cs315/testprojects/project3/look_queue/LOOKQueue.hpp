/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#ifndef __LOOKQueue_hpp
#define __LOOKQueue_hpp

#include<iostream>

#include "LOOKQueueNode.hpp"

class Request;

class LOOKQueue: public Queue {

public:
    LOOKQueue(): head(nullptr), tail(nullptr), firstNode(nullptr), currentTrack(0), currentSector(0), numReq(0), firstTime(0), completedReq(0), firstTrack(0), numTracks(0) {}

    virtual void addRequest(Request *request);
    virtual Request *getRequest();
    virtual bool isEmpty();
    virtual void print();
    virtual ~LOOKQueue();

private:
    LOOKQueueNode *head, *tail, *firstNode;
    int currentTrack;
    int currentSector;
    double firstTime;
    int firstTrack;
    int numReq;
    int completedReq;
    int numTracks;

    //helper functions
    void InsertFirst (Request * request);
    void InsertLast (Request * request);
    bool DeleteFirst ();
    bool DeleteLast ();
    bool Delete (int trackToDelete);
};


#endif
