/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#ifndef PROJECT5_JSONDATAITEM_H
#define PROJECT5_JSONDATAITEM_H

#include <string>
#include <fstream>

class JSONDataItem {
public:

    JSONDataItem(): _attribute(""), _svalue(""), hasReadAnItem(false), _isNumber(false) {}
    void parseJSONItem(std::fstream &stream);

    std::string attribute() { return _attribute; }

    int integerValue() { return _ivalue; }
    std::string stringValue() { return _svalue; }

    bool isNumber() { return _isNumber; }

    //void print();  // purely for debugging -- any format you want UNCOMMENT

private:

    std::string _attribute, _svalue;
    int _ivalue;
    bool hasReadAnItem, _isNumber;

    //std::string readQuotedString(std::fstream &stream); UNCOMMENT
};


#endif //PROJECT5_JSONDATAITEM_H

/*

For example, an instance of this class would represent the following item.
"artist_name": "Beatles, The"

Another instance of this class could represent this item
"album_id": 82730

 */