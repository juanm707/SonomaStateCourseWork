/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#include "Request.hpp"
#include "CLOOKQueue.hpp"
#include <fstream>
#include <iostream>


int main() {

    CLOOKQueue * clook = new CLOOKQueue();

    double time;
    int track;
    int sector;
    
    while (std::cin >> time) {

      std::cin >> track >> sector;
      Request * req = new Request(time,track,sector);
      clook->addRequest(req);
    }

    clook->print();

    delete clook;
    
    return 0;
}

