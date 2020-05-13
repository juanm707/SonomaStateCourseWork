/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#ifndef PROJECT3_TIMEREVENT_HPP
#define PROJECT3_TIMEREVENT_HPP

class TimerEvent {

public:
    TimerEvent(double timer): time(timer) {}
    ~TimerEvent();
    double getTime() { return time; }


private:
    double time;
};

#endif //PROJECT3_TIMEREVENT_HPP
