/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#include "Request.hpp"
#include "LOOKQueue.hpp"
#include <fstream>
#include <iostream>


int main() {

    LOOKQueue * look = new LOOKQueue();

    double time;
    int track;
    int sector;
    
    while (std::cin >> time) {

      std::cin >> track >> sector;
      Request * req = new Request(time,track,sector);
      look->addRequest(req);
    }

    look->print();

    delete look;
    
    return 0;
}

