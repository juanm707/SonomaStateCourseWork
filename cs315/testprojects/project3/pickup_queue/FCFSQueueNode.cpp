/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
class Request;

#include "FCFSQueueNode.hpp"

FCFSQueueNode::FCFSQueueNode(Request *req, FCFSQueueNode *nextPtr): _request(req), _next(nextPtr) {}
FCFSQueueNode::FCFSQueueNode(Request *req): _request(req), _next(nullptr) {}
FCFSQueueNode *FCFSQueueNode::next() { 
    return _next; 
}

void FCFSQueueNode::next(FCFSQueueNode *node) { 
    _next = node; 
}

Request *FCFSQueueNode::request() { 
    return _request; 
}
