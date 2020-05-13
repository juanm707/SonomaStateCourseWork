/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#include "Request.hpp"
#include "FCFSQueue.hpp"
#include "CLOOKQueue.hpp"
#include "EventNode.hpp"
#include "EventQueue.hpp"
#include "CLOOKDisk.h"
#include <fstream>
#include <iostream>


int main() {

    CLOOKQueue * look = new CLOOKQueue();
    CLOOKDisk * clook_disk = new CLOOKDisk(look);

    EventQueue * eventQ = new EventQueue();

    int time;
    int track;
    int sector;

    int i = 0;

    std::cin >> time >> track >> sector;

    Request * req = new Request(time,track,sector);
    RequestEvent * reqEvent = new RequestEvent(req);
    EventNode * eventN = new EventNode();
    eventN->addRequest(reqEvent);
    
    eventQ->addEvent(eventN);

    EventNode *timeN = new EventNode();
    TimerEvent *timeEvent = new TimerEvent(50);
    timeN->addTimer(timeEvent);
    eventQ->addEvent(timeN);
    
    while (!eventQ->isEmpty()) {

        EventNode * ev = eventQ->popEvent();
        eventQ->setTime(ev->getNum());
       	 
        /*-------------------------------------------------------------*/
        if (ev->isRequestEvent()) {
            //add the next request std::cin >> time track sector
	  if (!std::cin.eof()) {
	        std::cin >> time >> track >> sector;
		
                Request *req_2 = new Request(time, track, sector);
                RequestEvent *reqEvent = new RequestEvent(req_2);
                EventNode *eventN = new EventNode();
                eventN->addRequest(reqEvent);
		
                eventQ->addEvent(eventN);
                i++;
            }

            DiskDoneEvent * evR = clook_disk->proccessRequest(ev->getRequest(),eventQ->getTime());

            if (evR != nullptr) {
                EventNode * RtoD = new EventNode();
                RtoD->addDiskDone(evR);
                eventQ->addEvent(RtoD);
            }

        }

        else if (ev->isDiskDoneEvent()) {

            std::string qType = ev->getDiskDone()->getQ();
            if (qType == "clook") { // else if strack pickup look clook
                DiskDoneEvent *evD = clook_disk->proccessDiskDone(ev->getDiskDone(), eventQ->getTime());
                if (evD != nullptr) {
                    EventNode *DtoD = new EventNode();
                    DtoD->addDiskDone(evD);
                    eventQ->addEvent(DtoD);
                }
                else {
                    //do nothing
                }
            }
        }

        else if (ev->isTimerEvent()){ // ev is a timer event

            if (!eventQ->isEmpty()) {

                TimerEvent * newTime = new TimerEvent(eventQ->getTime() + 50);
                EventNode * TtoT = new EventNode();
                TtoT->addTimer(newTime);
                eventQ->addEvent(TtoT);
		
            }
        }

        /*------------------------------------------------------------*/
    }
    
    clook_disk->printSummary();

    delete look;
    delete clook_disk;
    delete req;
    delete timeN;

    return 0;
}
