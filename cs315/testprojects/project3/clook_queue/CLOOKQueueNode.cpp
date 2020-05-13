/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#include "CLOOKQueueNode.hpp"

CLOOKQueueNode::CLOOKQueueNode(int track, CLOOKQueueNode *nextPtr, CLOOKQueueNode *prevPtr): trackNum(track), _next(nextPtr), _prev(prevPtr) {STRACKq = new FCFSQueue();}

CLOOKQueueNode::CLOOKQueueNode(int track): trackNum(track), _next(nullptr), _prev(nullptr) { STRACKq = new FCFSQueue();}

CLOOKQueueNode * CLOOKQueueNode::next() {
    return _next;
}
CLOOKQueueNode * CLOOKQueueNode::prev() {
    return _prev;
}

void CLOOKQueueNode::next(CLOOKQueueNode *node) {
    _next = node;
}

void CLOOKQueueNode::prev(CLOOKQueueNode *node) {
    _prev = node;
}

int CLOOKQueueNode::STtrack() {
    return trackNum;
}

FCFSQueue * CLOOKQueueNode::getQ() {
    return STRACKq;
}
