#ifndef __PICKUPQueueNode_hpp
#define __PICKUPQueueNode_hpp

#include "FCFSQueue.hpp"

class Request;

class PICKUPQueueNode {
public:
    PICKUPQueueNode(int track, PICKUPQueueNode *nextPtr);
    PICKUPQueueNode(int track);
    PICKUPQueueNode *next();
    PICKUPQueueNode *prev();
    void next(PICKUPQueueNode *node);
    void prev(PICKUPQueueNode * pNode);
    int PUtrack();
    int nextTrack();
    void setNextTrack(int next);
    FCFSQueue * getQ();

private:
    PICKUPQueueNode *_next;
    PICKUPQueueNode *_prev;
    int trackNum;
    int nextToDo;
    FCFSQueue * STRACKq;
};

#endif