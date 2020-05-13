/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#ifndef PROJECT3_DISKDONEEVENT_H
#define PROJECT3_DISKDONEEVENT_H

#include "string"

class DiskDoneEvent {
public:
    DiskDoneEvent(float _time, std::string & forQ): time(_time), queue(forQ) {}
    ~DiskDoneEvent();
    double getTime() { return time;}
    std::string getQ() { return queue;}

private:

    double time;
    std::string queue;

};

#endif //PROJECT3_DISKDONEEVENT_H
