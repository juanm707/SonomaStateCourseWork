/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#ifndef __CLOOKQueueNode_hpp
#define __CLOOKQueueNode_hpp

#include "FCFSQueue.hpp"

class Request;

class CLOOKQueueNode {
public:
    CLOOKQueueNode(int track, CLOOKQueueNode *nextPtr, CLOOKQueueNode *prevPtr);
    CLOOKQueueNode(int track);
    CLOOKQueueNode *next();
    CLOOKQueueNode *prev();
    void next(CLOOKQueueNode *node);
    void prev(CLOOKQueueNode *node);
    int STtrack();
    FCFSQueue * getQ();

private:
    CLOOKQueueNode *_next;
    CLOOKQueueNode *_prev;
    int trackNum;
    FCFSQueue * STRACKq;
};

#endif
