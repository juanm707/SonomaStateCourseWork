/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#include "STRACKQueueNode.hpp"

STRACKQueueNode::STRACKQueueNode(int track, STRACKQueueNode *nextPtr): trackNum(track), _next(nextPtr) { STRACKq = new FCFSQueue();}

STRACKQueueNode::STRACKQueueNode(int track): trackNum(track), _next(nullptr) { STRACKq = new FCFSQueue(); }

STRACKQueueNode * STRACKQueueNode::next() {
    return _next;
}

void STRACKQueueNode::next(STRACKQueueNode * node) {
    _next = node;
}

FCFSQueue * STRACKQueueNode::getQ() {
    return STRACKq;
}

int STRACKQueueNode::STtrack() {
    return trackNum;
}
