/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#ifndef __Request_hpp
#define __Request_hpp

class Request {
public:
    Request(double rTime, int rTrack, int rSector):  _time(rTime), _track(rTrack), _sector(rSector) {}

    int track()    { return _track;  }
    int sector()   { return _sector; }
    double time()  { return _time;   }

private:
    double _time;
    int _track, _sector;

};

#endif
