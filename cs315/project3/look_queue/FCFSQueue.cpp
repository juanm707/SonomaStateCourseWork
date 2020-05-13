/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#include "FCFSQueue.hpp"
#include "Request.hpp"
#include <cmath>
#include <iomanip>

void FCFSQueue::addRequest(Request *request) {
  
    FCFSQueueNode *rNode = new FCFSQueueNode(request);
    if( isEmpty() ) {
        head = tail = rNode;
        firstTime = request->time();
        numReq++;
    } else {
        tail->next(rNode);
        tail = rNode;
        numReq++;
    }
}

Request *FCFSQueue::getRequest() {
    if( isEmpty() ) {
        std::cout << "Calling FCFSQueue::getRequest() on empty queue. Terminating...\n";
        exit(1);
    }

    Request * copy = head->request();
    head = head->next();
    if (head == nullptr)
        tail = nullptr;
    return copy;
}

bool FCFSQueue::isEmpty() { 
    return head == nullptr; 
}

void FCFSQueue::print() {
  
    for(auto cur = head; cur; cur = cur->next()) {     
        Request *cReq = cur->request();
	std::cout << cReq->time() << " " << cReq->track() << " " << cReq->sector() << std::endl;
    }
}

FCFSQueue::~FCFSQueue() {
    while( head != nullptr ) {
        FCFSQueueNode *node = head;
        head = node->next();
        delete node;
    }        
}
