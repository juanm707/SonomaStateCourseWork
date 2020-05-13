/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#ifndef PROJECT3_REQUESTEVENT_H
#define PROJECT3_REQUESTEVENT_H

class Request;

 class RequestEvent {
 public:
     RequestEvent(Request * req): request(req) {}
     ~RequestEvent();
     Request * getReq() {return request;}

 private:
     Request * request;


 };

#endif //PROJECT3_REQUESTEVENT_H
