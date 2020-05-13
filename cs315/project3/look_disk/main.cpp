/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#include "Request.hpp"
#include "FCFSQueue.hpp"
#include "LOOKQueue.hpp"
#include "EventNode.hpp"
#include "EventQueue.hpp"
#include "LOOKDisk.h"
#include <fstream>
#include <iostream>


int main() {

    LOOKQueue * look = new LOOKQueue();
    LOOKDisk * look_disk = new LOOKDisk(look);

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

            DiskDoneEvent * evR = look_disk->proccessRequest(ev->getRequest(),eventQ->getTime());

            if (evR != nullptr) {
                EventNode * RtoD = new EventNode();
                RtoD->addDiskDone(evR);
                eventQ->addEvent(RtoD);
            }

        }

        else if (ev->isDiskDoneEvent()) {

            std::string qType = ev->getDiskDone()->getQ();
            if (qType == "look") { // else if strack pickup look clook
                DiskDoneEvent *evD = look_disk->proccessDiskDone(ev->getDiskDone(), eventQ->getTime());
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
    
    look_disk->printSummary();

    delete look;
    delete look_disk;
    delete req;
    delete timeN;

    return 0;
}

