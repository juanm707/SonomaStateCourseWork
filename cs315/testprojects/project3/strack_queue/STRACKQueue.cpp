/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#include "STRACKQueue.hpp"
#include "Request.hpp"
#include "cmath"
#include "iomanip"

void STRACKQueue::addRequest(Request *request) {

    if (isReallyEmpty()) {
        STRACKQueueNode *rNode = new STRACKQueueNode(request->track());
        FCFSQueue * add = rNode->getQ();
        add->addRequest(request);
        numReq++;
        head = tail = rNode;
        firstTime = request->time();
        numTracks++;
    }

    else {
        STRACKQueueNode *node = head;
        while (node != nullptr) { //check if track number is already in queue nodes
            if (node->STtrack() == request->track()) {
                FCFSQueue * add = node->getQ();
                add->addRequest(request);
                numReq++;
                return;
            }
            else {
                node = node->next();
            }
        }
        STRACKQueueNode * newNode = new STRACKQueueNode(request->track());
        FCFSQueue * add = newNode->getQ();
        add->addRequest(request);
        numReq++;
        tail->next(newNode);
        tail = newNode;
        numTracks++;
    }
}

Request *STRACKQueue::getRequest() {
    if (isReallyEmpty() || isEmpty()) {
        std::cout << "Calling STRACKQueue::getRequest() on empty queue. Terminating...\n";
        exit(1);
    }

    STRACKQueueNode * nCopy = head;
    while(nCopy != nullptr) {

        FCFSQueue *qCopy = nCopy->getQ();
        while (!qCopy->isEmpty()) {
            Request *rCopy = qCopy->getRequest();
            completedReq++;
            return rCopy;
        }
	
        nCopy = nCopy->next();
    }
}

bool STRACKQueue::isEmpty() {
  //if the queues are there but have no requests
    int i = 0;
    int count = 0;
    STRACKQueueNode * copy = head;

    while (copy != nullptr) {

        if (copy->getQ()->isEmpty())
            count++;
        copy = copy->next();
    }

    if (count == numTracks )
        return true;
    else
        return false;
}

bool STRACKQueue::isReallyEmpty() {
    return head == nullptr;
}

void STRACKQueue::print() {

    for (auto cur = head; cur; cur = cur->next()) {
        cur->getQ()->print();
    }
}

STRACKQueue::~STRACKQueue() {
    while( head != nullptr ) {
        STRACKQueueNode *node = head;
        head = node->next();
        delete node;
    }
}
