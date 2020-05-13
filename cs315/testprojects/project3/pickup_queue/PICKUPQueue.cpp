/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#include "PICKUPQueue.hpp"
#include "Request.hpp"
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>

void PICKUPQueue::addRequest(Request *request) {

    if (isEmpty()) {
        PICKUPQueueNode *rNode = new PICKUPQueueNode(request->track());
        firstTrack = request->track();
        FCFSQueue * add = rNode->getQ();
        add->addRequest(request);
        numReq++;
        head = tail = rNode;
        firstTime = request->time();
        orderOf.push_back(request->track());
    }

    else {
        PICKUPQueueNode *node = head;
        while (node != nullptr) {
            if (node->PUtrack() == request->track()) {
                FCFSQueue * add = node->getQ();
                add->addRequest(request);
                numReq++;
                //orderOf.push_back(request->track());
                return;
            }
            else {
                node = node->next();
            }
        }
        PICKUPQueueNode * newNode = new PICKUPQueueNode(request->track());
        FCFSQueue * add = newNode->getQ();
        add->addRequest(request);
        numReq++;
        PICKUPQueueNode * temp = tail;
        tail->next(newNode);
        tail = newNode;
        tail->prev(temp);
        orderOf.push_back(request->track());
    }

}

Request * PICKUPQueue::getRequest() {

    if (isEmpty() || orderOf.empty()) {
        std::cout << "Calling PICKUPQueue::getRequest() on empty queue. Terminating...\n";
        exit(1);
    }
    if (order) {
        PICKUPQueueNode *nCopy = head;
        while (nCopy->PUtrack() != orderOf[0]) {
            nCopy = nCopy->next();
        }
        FCFSQueue *qCopy = nCopy->getQ();
        while (!qCopy->isEmpty()) {
            Request *rCopy = qCopy->getRequest();
            completedReq++;
            return rCopy;
        }

        orderOf.erase(orderOf.begin());

        if (head == nullptr)
            tail = nullptr;
        return getRequest();
    }

    else {

        std::vector<int> doThese;

        if (orderOf.size() == 1) {
            order = true;
            return getRequest();
        }

        if(orderOf.size() > 1) {
            if(orderOf[0] > orderOf[1])
                std::sort(orderOf.rbegin(),orderOf.rend()); // 79 > 47 if 47 first then 79, then sort normally.
            else
                std::sort(orderOf.begin(),orderOf.end());
        }

        PICKUPQueueNode * current = head;
        PICKUPQueueNode * currentNext = current->next();

        while (currentNext != nullptr) {
            inBetween(doThese, current->PUtrack(), currentNext->PUtrack());
            current = currentNext;
            currentNext = current->next();
        }
        order = true;
        orderOf = doThese;

        return getRequest();
    }
}
bool PICKUPQueue::isEmpty() {
    return head == nullptr;
}
void PICKUPQueue::print() {

  while (completedReq != numReq) {
    Request * print = getRequest();
    std::cout << print->time() << ' ' << print->track() << ' ' << print->sector() << std::endl;
  }      
}


PICKUPQueue::~PICKUPQueue() {
    while( head != nullptr ) {
        PICKUPQueueNode *node = head;
        head = node->next();
        delete node;
    }
}

void PICKUPQueue::inBetween (std::vector<int> & orderedVec, int first, int last) {

    if (first > last) {
        for (int i = 0; i != orderOf.size(); i++) {
            if (orderOf[i] >= last && orderOf[i] <= first) {
                if (std::find(orderedVec.begin(), orderedVec.end(), orderOf[i]) != orderedVec.end()){
                    //do nothing
                }
                else
                    orderedVec.push_back(orderOf[i]);
            }
        }
    }
    else if (last > first) {
        for (int i = 0; i != orderOf.size(); i++) {
            if (orderOf[i] >= first && orderOf[i] <= last) {
                if (std::find(orderedVec.begin(), orderedVec.end(), orderOf[i]) != orderedVec.end()) {
                    //do nothing
                }
                else
                    orderedVec.push_back(orderOf[i]);
            }
        }
    }
}
