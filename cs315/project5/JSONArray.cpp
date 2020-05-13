/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#include <vector>
#include <iostream>
#include "JSONArray.hpp"

JSONArray::~JSONArray() {

}

void JSONArray::parseJSONArray(std::fstream &stream) {

    char cc[2], prev = ' ';
    cc[1] = '\0';

    if (!(stream >> cc[0]) || cc[0] != '[') { // we expect this to be a open-bracket character.
        // print an error message and exit
        std::cerr << "EXPECTED [ ... (in JSONArray.cpp\n";
    }

    do {
        JSONDataObject *dItem = jsonObjectNode();
        dItem->parseFromJSONstream(stream);
        _listOfDataObjects->push_back(dItem);

        if (!(stream >> cc[0])) {
            // print an error message and exit
        }

        if (cc[0] != ']' && cc[0] != ',') {
            // print an error message and exit
        }

    } while (cc[0] != ']');
}
