/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#include <iostream>
#include <vector>
#include "JSONDataObject.hpp"
#include "JSONDataItem.hpp"

void JSONDataObject::parseFromJSONstream(std::fstream &stream) {

    char c;

    if( !(stream >> c) || c != '{' ) { // The first non-space character of a JSON object has to be '{'.
        // print some error message and exit the program.
        std::cerr << "Expected {\n";
        exit(3);
    }

    do {

        JSONDataItem * jsonDI = new JSONDataItem();
        jsonDI->parseJSONItem(stream);
        _listOfDataItems->push_back(jsonDI);

        //readJSONDataItem(stream);   // we know that a JSON object has at least one JSON key/value pair.
        // readJSONDataItem reads exactly one such pair.
        stream >> c;  // the character after the JSON key/value pair is either a comma, indicating
        // there are more key/value pairs to be read, or a closed-brace ('}').
        // A closed-brace means that we have already read all JSON key/value pairs.
    } while( c != '}' );

}

std::string JSONDataObject::valueForStringAttribute(std::string s) {

    for (auto const &dataItem: *_listOfDataItems) {
        if (dataItem->attribute() == s)
            return dataItem->stringValue();
    }

    return "n/a";
}

int JSONDataObject::valueForIntegerAttribute(std::string s) {

    for (auto const &dataItem: *_listOfDataItems) {
        if (dataItem->attribute() == s)
            return dataItem->integerValue();
    }

    return -1;
}