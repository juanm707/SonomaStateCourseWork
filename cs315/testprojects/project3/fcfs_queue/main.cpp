/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#include "Request.hpp"
#include "FCFSQueue.hpp"
#include <fstream>
#include <iostream>


int main() {

    FCFSQueue * fcfs = new FCFSQueue();

    double time;
    int track;
    int sector;
    
    while (std::cin >> time) {

      std::cin >> track >> sector;
      Request * req = new Request(time,track,sector);
      fcfs->addRequest(req);
    }

    fcfs->print();

    delete fcfs;
    
    return 0;
}

