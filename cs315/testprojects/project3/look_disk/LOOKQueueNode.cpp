/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#include "LOOKQueueNode.hpp"

LOOKQueueNode::LOOKQueueNode(int track, LOOKQueueNode *nextPtr, LOOKQueueNode *prevPtr): trackNum(track), _next(nextPtr), _prev(prevPtr) {STRACKq = new FCFSQueue();}

LOOKQueueNode::LOOKQueueNode(int track): trackNum(track), _next(nullptr), _prev(nullptr) { STRACKq = new FCFSQueue();}

LOOKQueueNode * LOOKQueueNode::next() {
    return _next;
}
LOOKQueueNode * LOOKQueueNode::prev() {
    return _prev;
}

void LOOKQueueNode::next(LOOKQueueNode *node) {
    _next = node;
}

void LOOKQueueNode::prev(LOOKQueueNode *node) {
    _prev = node;
}

int LOOKQueueNode::STtrack() {
    return trackNum;
}

FCFSQueue * LOOKQueueNode::getQ() {
    return STRACKq;
}
