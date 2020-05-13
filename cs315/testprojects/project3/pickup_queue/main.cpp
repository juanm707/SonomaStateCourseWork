/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#include "Request.hpp"
#include "PICKUPQueue.hpp"
#include <fstream>
#include <iostream>


int main() {

    PICKUPQueue * pickup = new PICKUPQueue();

    double time;
    int track;
    int sector;
    
    while (std::cin >> time) {

      std::cin >> track >> sector;
      Request * req = new Request(time,track,sector);
      pickup->addRequest(req);
    }

    pickup->print();

    delete pickup;
    
    return 0;
}

