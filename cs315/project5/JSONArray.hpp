/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#ifndef PROJECT5_JSONARRAY_H
#define PROJECT5_JSONARRAY_H

#include "JSONDataObject.hpp"

class JSONArray {
public:

    JSONArray() { _listOfDataObjects = new std::vector<JSONDataObject *>; }
    ~JSONArray();

    std::vector<JSONDataObject *> *listOfDataObjects() { return _listOfDataObjects; }
    virtual JSONDataObject *jsonObjectNode() = 0;
    int numJSONObjects() { return _listOfDataObjects->size(); }
    void parseJSONArray(std::fstream &stream);

    //virtual void print();

protected:
    std::vector<JSONDataObject *> *_listOfDataObjects;

};

#endif //PROJECT5_JSONARRAY_H
