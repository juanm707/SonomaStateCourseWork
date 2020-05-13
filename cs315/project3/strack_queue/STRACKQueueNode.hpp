/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#ifndef __STRACKQueueNode_hpp
#define __STRACKQueueNode_hpp

#include "FCFSQueue.hpp"

class Request;

class STRACKQueueNode {
public:
    STRACKQueueNode(int track, STRACKQueueNode *nextPtr);
    STRACKQueueNode(int track);
    STRACKQueueNode *next();
    void next(STRACKQueueNode *node);
    int STtrack();
    FCFSQueue * getQ();

private:
    STRACKQueueNode *_next;
    int trackNum;
    FCFSQueue * STRACKq;
};

#endif
