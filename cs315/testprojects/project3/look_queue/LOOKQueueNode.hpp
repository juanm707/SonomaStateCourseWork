/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#ifndef __LOOKQueueNode_hpp
#define __LOOKQueueNode_hpp

#include "FCFSQueue.hpp"

class Request;

class LOOKQueueNode {
public:
    LOOKQueueNode(int track, LOOKQueueNode *nextPtr, LOOKQueueNode *prevPtr);
    LOOKQueueNode(int track);
    LOOKQueueNode *next();
    LOOKQueueNode *prev();
    void next(LOOKQueueNode *node);
    void prev(LOOKQueueNode *node);
    int STtrack();
    FCFSQueue * getQ();

private:
    LOOKQueueNode *_next;
    LOOKQueueNode *_prev;
    int trackNum;
    FCFSQueue * STRACKq;
};

#endif
