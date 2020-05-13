/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#include "PICKUPQueueNode.hpp"

PICKUPQueueNode::PICKUPQueueNode(int track, PICKUPQueueNode *nextPtr): trackNum(track), nextToDo(-1), _next(nextPtr), _prev(nullptr) { STRACKq = new FCFSQueue();}

PICKUPQueueNode::PICKUPQueueNode(int track): trackNum(track), nextToDo(-1), _next(nullptr), _prev(nullptr) { STRACKq = new FCFSQueue();}

PICKUPQueueNode * PICKUPQueueNode::next() {
    return _next;
}

PICKUPQueueNode * PICKUPQueueNode::prev() {
    return _prev;
}

void PICKUPQueueNode::next(PICKUPQueueNode *node) {
    _next = node;
}

void PICKUPQueueNode::prev(PICKUPQueueNode *pNode) {
    _prev = pNode;
}

int PICKUPQueueNode::PUtrack() {
    return trackNum;
}

int PICKUPQueueNode::nextTrack() {
    return nextToDo;
}
void PICKUPQueueNode::setNextTrack(int next) {
    nextToDo = next;
}

FCFSQueue * PICKUPQueueNode::getQ() {
    return STRACKq;
}
