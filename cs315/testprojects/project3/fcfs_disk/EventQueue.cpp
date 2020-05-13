/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#include "EventQueue.hpp"
#include <iostream>
#include "Request.hpp"

void EventQueue::addEvent(EventNode *event) {

    if (numEvents == 0)
    {
        InsertFirst(event);
        return;
    }


    else if (event->getNum() <= head->getNum())
    {
        InsertFirst(event);
        return;
    }

    else if (event->getNum() >= tail->getNum())
    {
        InsertLast(event);
        return;
    }

    else {

        EventNode *nn = event;

        //Traverse the list
        EventNode * nx = head;
        while (nx->getNum() < event->getNum()) {
            nx = nx->next();
        }

        EventNode * pv = nx->prev();
        nn->prev(pv);
        nx->prev(nn);
        pv->next(nn);
        nn->next(nx);
        numEvents++;
        return;
    }

}

EventNode * EventQueue::popEvent() {

    if( isEmpty() ) {
        std::cout << "Calling EventQueue::popEvent() on empty queue. Terminating...\n";
        exit(1);
    }

    EventNode * copy = head;
    head = head->next();
    if (head == nullptr)
        tail = nullptr;
    return copy;
}

void EventQueue::printQ() {

    if( isEmpty() ) {
        std::cout << "\tEMPTY\n";
        return;
    }

    EventNode * copy = head;
    while ( copy != nullptr ) {

        if (copy->isRequestEvent()) {
            Request *printR = copy->getRequest()->getReq();
            std::cout << "\t" << "(req " << printR->time() << ' ' << printR->track() << ' ' << printR->sector() << ')' << std::endl;
        }

        else if (copy->isTimerEvent()) {
            TimerEvent *printT = copy->getTimer();
            std::cout << "\t" << "(timer " << printT->getTime() << ')' << std::endl;
        }

        else { //its a disk done event
            DiskDoneEvent *printD = copy->getDiskDone();
            std::cout << "\t" << "(ddone " << printD->getTime() << ' ' << printD->getQ() << ')' << std::endl;
        }

        copy = copy->next();
    }

    std::cout << std::endl;
    return;
}

EventQueue::~EventQueue() {

    while( head != nullptr ) {
        EventNode *node = head;
        head = node->next();
        delete node;
    }

}

// HELPER FUNCTIONS
void EventQueue::InsertFirst(EventNode * eventN) {

    EventNode *nw = eventN;
    if (numEvents == 0) {
        nw->next(nullptr);
        nw->prev(nullptr);
        head = nw;
        tail = nw;
        numEvents++;
        return;
    }

    else if (numEvents >= 1) {
        nw->next(head);
        nw->prev(nullptr);
        head->prev(nw);
        head = nw;
        numEvents++;
        return;
    }

}

void EventQueue::InsertLast(EventNode *eventN) {

    if (numEvents == 0) {
        InsertFirst(eventN);
    }

    else if (numEvents > 0 ) {
        EventNode *nw = eventN;

        nw->next(nullptr);
        nw->prev(tail);

        tail->next(nw);
        tail = nw;
        numEvents++;
        return;
    }
}
