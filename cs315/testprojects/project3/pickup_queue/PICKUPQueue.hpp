/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#include<iostream>

#include "PICKUPQueueNode.hpp"
#include <vector>

class Request;

class PICKUPQueue: public Queue {

public:
    PICKUPQueue(): head(nullptr), tail(nullptr), order(false), firstTrack(0), currentTrack(0), currentSector(0), numReq(0), firstTime(0), completedReq(0) {}

    virtual void addRequest(Request *request);
    virtual Request *getRequest();
    virtual bool isEmpty();
    virtual void print();
    virtual ~PICKUPQueue();

private:
    PICKUPQueueNode *head, *tail;

    std::vector<int> orderOf; //orders the tracks in correct order for pickup

    void inBetween (std::vector<int> & orderedVec, int first, int last); //vector stores the correct order of Nodes, NOT the nodes themselves

    bool order;

    int firstTrack;
    int currentTrack;
    int currentSector;
    double firstTime;
    int numReq;
    int completedReq;
};
