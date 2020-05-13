/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#ifndef __FCFSQueueNode_hpp
#define __FCFSQueueNode_hpp

class Request;

class FCFSQueueNode {
public:
    FCFSQueueNode(Request *req, FCFSQueueNode *nextPtr);
    FCFSQueueNode(Request *req);
    FCFSQueueNode *next();
    void next(FCFSQueueNode *node);
    Request *request();
    void setDone() { done = true;}
    bool isDone() { return done; }

private:
    FCFSQueueNode *_next;
    Request *_request;
    bool done;
};

#endif
