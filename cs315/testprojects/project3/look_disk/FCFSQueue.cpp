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
        head = tail = start = rNode;
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

Request * FCFSQueue::getCopyRequest() {
    if (isEmpty()) {
        std::cout << "Calling FCFSQueue::getCopyRequest() on empty queue. Terminating...\n";
        exit(1);
    }

    FCFSQueueNode *copy = start;
    Request *reqCopy = start->request();
    start = start->next();
    return reqCopy;
}

bool FCFSQueue::isEmpty() {
    return head == nullptr;
}

void FCFSQueue::print() {

    /*int width = 10;

    std::cout << "FCFS REPORT" << std::endl;
    std::cout << std::left
              << std::setw(width) << '#'
              << std::setw(width) << "Trac"
              << std::setw(width) << "Sec"
              << std::setw(width) << "Entr"
              << std::setw(width) << "Init"
              << std::setw(width) << "Comp"
              << std::setw(width) << "Wait"
              << std::setw(width) << "Serv"
              << std::setw(width) << "TmInSys" << std::endl;

    int i = 0;
    double init = firstTime * 0.1;*/

    for(auto cur = head; cur; cur = cur->next()) {

        Request *cReq = cur->request();
        std::cout << "\t\t" << cReq->time() << " " << cReq->track() << " " << cReq->sector() << std::endl;

        /*int track = cReq->track();
        int sector = cReq->sector();
        //std::cout << "Current Sector: " << currentSector << ' ' << "Dest sector: " << sector << std::endl;
        double entr = cReq->time() * 0.1;

        double seekTime = abs(currentTrack - track) * 3;
        double rotationalD = 0;
        if (currentSector < sector) {
            rotationalD = abs(currentSector - sector) * 0.1;
        } else if (currentSector > sector) {
            //rotationalD = ((currentSector - sector) * 2) * 0.1;
            rotationalD = ((30 - currentSector) + sector) * 0.1;
        }
        float transferTime = 0.1;
        double serve = seekTime + rotationalD + transferTime;
        std::cout << "Serve:: " << serve << std::endl;
        double comp = init + serve;
        double wait = init - entr;
        double timeIn = comp - entr;

        //std::cout << "Seektime: " << seekTime << ' ' << "Rotatioanl delay: " << ' ' << rotationalD << ' ' << "Transfer Time: " << ' ' << transferTime << std::endl;
        std::cout << std::left << std::setw(width)
                  << i + 1
                  << std::setw(width) << track
                  << std::setw(width) << sector
                  << std::setw(width) << std::fixed
                  << std::setprecision(2) << entr
                  << std::setw(width) << init
                  << std::setw(width) << comp
                  << std::setw(width) << wait
                  << std::setw(width) << serve
                  << std::setw(width) << timeIn
                  << std::endl;
        init = comp;
        currentSector = sector + 1;
        currentTrack = track;
        i++;*/
    }
}

FCFSQueue::~FCFSQueue() {
    while( head != nullptr ) {
        FCFSQueueNode *node = head;
        head = node->next();
        delete node;
    }        
}
