/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#ifndef PROJECT5_JSONDATAOBJECT_H
#define PROJECT5_JSONDATAOBJECT_H

#include <string>
#include <fstream>
#include <vector>
#include "JSONDataItem.hpp"

class JSONDataObject {
public:

    JSONDataObject() { _listOfDataItems = new std::vector<JSONDataItem *>; }
    virtual ~JSONDataObject() {}

    std::vector<JSONDataItem *> *listOfDataItems() const { return _listOfDataItems; }
    void parseFromJSONstream(std::fstream &stream);

    //virtual void print();

    std::string valueForStringAttribute(std::string s);
    int valueForIntegerAttribute(std::string s);

private:
    std::vector<JSONDataItem *> *_listOfDataItems; // new
};

#endif //PROJECT5_JSONDATAOBJECT_H
