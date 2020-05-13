/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 3
*/

#include "CLOOKDisk.h"
#include <cmath>
#include "Request.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>

DiskDoneEvent * CLOOKDisk::proccessRequest ( RequestEvent * reqEvent, int currentT ) {

    int width = 10;
    if (write == 0) {

        std::ofstream lookOutput;
        lookOutput.open("./CLOOK_output.txt");

        lookOutput << "CLOOK REPORT" << std::endl;
        lookOutput << std::left
                   << std::setw(width) << '#'
                   << std::setw(width) << "Trac"
                   << std::setw(width) << "Sec"
                   << std::setw(width) << "Entr"
                   << std::setw(width) << "Init"
                   << std::setw(width) << "Comp"
                   << std::setw(width) << "Wait"
                   << std::setw(width) << "Serv"
                   << std::setw(width) << "TmInSys" << std::endl;
        write = 1;
        lookOutput.close();
        init = reqEvent->getReq()->time() * 0.1;
    }

    waitQueue->addRequest(reqEvent->getReq());

    if (state == 0) {

        Request * getReq = reqEvent->getReq();

        // calculate serivce time
        double seekTime = abs(_track - getReq->track()) * 3;
        double rotationalD = 0;

        if (_sector < getReq->sector()) {

            rotationalD = abs(_sector - getReq->sector()) * 0.1;

        } else if (_sector > getReq->sector()) {

            rotationalD = ((30 - _sector) + getReq->sector()) * 0.1;
        }

        float transferTime = 0.1;
        double serve = seekTime + rotationalD + transferTime;

        DiskDoneEvent *servEvent = new DiskDoneEvent( (serve + currentT) * 10, type);
        state = 1;

        server = getReq;

        return servEvent;
    }

    return nullptr;
}

DiskDoneEvent * CLOOKDisk::proccessDiskDone ( DiskDoneEvent * diskDoneE, int currentT ) {

    //calculate time in system
    int width = 10;

    if (!waitQueue->isEmpty()) { //same part as process request event

        Request *getReq = waitQueue->getRequest();
        if (getReq->track() == 99)
            std::cout;

        /*------------------------------------------------------------------*/

        std::ofstream lookOutput;
        lookOutput.open("./CLOOK_output.txt", std::ios_base::app);

        int track_v2 = getReq->track();
        int sector_v2 = getReq->sector();

        double entr_v2 = getReq->time() * 0.1;

        double seekTime_v2 = abs(_track - track_v2) * 3;
        double rotationalD_v2 = 0;

        if (_sector < sector_v2) {
            rotationalD_v2 = abs(_sector - sector_v2) * 0.1;

        } else if (_sector > sector_v2) {
            rotationalD_v2 = ((30 - _sector) + sector_v2) * 0.1;
        }
        float transferTime_v2 = 0.1;
        double serve_v2 = seekTime_v2 + rotationalD_v2 + transferTime_v2;

        double comp_v2 = init + serve_v2;
        double wait_v2 = init - entr_v2;
        double timeIn_v2 = comp_v2 - entr_v2;

	totalTS+=timeIn_v2;
	totalWT+=wait_v2;
	totalST+=serve_v2;

	if (timeIn_v2 < minTS)
	  minTS = timeIn_v2;
	if (timeIn_v2 > maxTS)
	  maxTS = timeIn_v2;

	if (wait_v2 < minWT)
	  minWT = wait_v2;
	if (wait_v2 > maxWT)
	  maxWT = wait_v2;

	if (serve_v2 < minST)
	  minST = serve_v2;
	if (serve_v2 > maxST)
	  maxST = serve_v2;

        lookOutput << std::left << std::setw(width)
                   << count + 1
                   << std::setw(width) << track_v2
                   << std::setw(width) << sector_v2
                   << std::setw(width) << std::fixed
                   << std::setprecision(2) << entr_v2
                   << std::setw(width) << init
                   << std::setw(width) << comp_v2
                   << std::setw(width) << wait_v2
                   << std::setw(width) << serve_v2
                   << std::setw(width) << timeIn_v2
                   << std::endl;
        init = comp_v2;
        count++;
        lookOutput.close();
        /*------------------------------------------------------------------*/

        _track = getReq->track();
        _sector = getReq->sector() + 1;

        if (!waitQueue->isEmpty()) {
            // calculate serivce time

            Request * nextReq = waitQueue->getCopyRequest();
            //waitQueue->addRequest(nextReq);

            double seekTime = abs(_track - nextReq->track()) * 3;
            double rotationalD = 0;

            if (_sector < nextReq->sector()) {

                rotationalD = abs(_sector - nextReq->sector()) * 0.1;

            } else if (_sector > nextReq->sector()) {

                rotationalD = ((30 - _sector) + nextReq->sector()) * 0.1;
            }

            float transferTime = 0.1;
            double serve = seekTime + rotationalD + transferTime;

            DiskDoneEvent *servEvent = new DiskDoneEvent(serve + currentT, type);
            state = 1;

            server = nextReq;

            return servEvent;
        }
    }

    state = 0;
    server = nullptr;
    return nullptr;
}

void CLOOKDisk::printDisk() {

    std::cout << "CLOOK:\n";
    std::cout << "\tHead Position:\n";
    std::cout << "\t\t-- track: " << _track << std::endl;
    std::cout << "\t\t-- sector: " << _sector << std::endl << std::endl;

    if (server == nullptr) {
        std::cout << "\tServer: READY" << std::endl << std::endl;
    }
    else {

        std::cout << "\tServer: (serv " << server->time() << ' ' << server->track() << ' ' << server->sector() << ')'
                  << std::endl << std::endl;
    }

    if (waitQueue->isEmpty()) {
        std::cout << "\tCLOOK Queue: EMPTY" << std::endl << std::endl;
    }
    else {
        std::cout << "\tCLOOK Queue:" << std::endl;
        waitQueue->print();
        std::cout << std::endl;
    }
}

void CLOOKDisk::printSummary() {

  int width = 10;
  std::ofstream fcfsOutput;
  fcfsOutput.open("./CLOOK_summary.txt");

  fcfsOutput << "SUMMARY REPORT" << std::endl;
  fcfsOutput << std::left
	     << std::setw(width) << "Name"
	     << std::setw(width*3.5) << "TimeInSystem"
	     << std::setw(width*4) << "WaitTime"
	     << std::setw(width*4) << "ServiceTime"
	     << std::endl;
  for (int i = 0; i < 3; i++) {
    fcfsOutput << std::right << std::setw(width + 2) << "Min" << std::setw(width + 2) << "Max"
	       << std::setw(width + 2) << "Avg";
  }
  fcfsOutput << std::endl << "FCFS " << std::fixed << std::setprecision(2) << std::setw(width) << minTS
	     << std::setw(width) << maxTS << std::setw(width) << totalTS/count
	     << std::setw(width+4) << minWT << std::setw(width) << maxWT << std::setw(width) << totalWT/count
	     << std::setw(width+7) << minST << std::setw(width) << maxST << std::setw(width) << totalST/count;

  fcfsOutput.close();
}
