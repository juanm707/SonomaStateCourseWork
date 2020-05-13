/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#include "Request.hpp"
#include "STRACKQueue.hpp"
#include <fstream>
#include <iostream>


int main() {

    STRACKQueue * strack = new STRACKQueue();

    double time;
    int track;
    int sector;
    
    while (std::cin >> time) {

      std::cin >> track >> sector;
      Request * req = new Request(time,track,sector);
      strack->addRequest(req);
    }
    
    strack->print();
    delete strack;
    return 0;
}

