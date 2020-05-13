/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 4
*/

#include<fstream>
#include<cstring>

class Artist
{
public:
    Artist(): _name(""), _realName(""), _profile(""), _numImages(0), _artistID(0) {}
    ~Artist();

    std::string profile()    { return _profile; }
    std::string name()       { return _name; }
    std::string realName()   { return _realName; }
    unsigned    numImages()  { return _numImages; }
    unsigned    artistID()   { return _artistID;  }

    void print();
    void parseFromJSONstream(std::fstream &stream);
    std::string htmlString();

private:
    std::string _name, _realName, _profile;
    unsigned _numImages, _artistID;

    // Private Functions
    void readJSONDataItem(std::fstream &stream);
};