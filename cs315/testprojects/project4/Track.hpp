/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 4
*/

#include<fstream>
#include<cstring>

class Track
{
public:
    Track(): _artistName(""), _title(""), _albumName(""), _duration("N/A"), _position(""), _albumID(0) {}
    ~Track();

    std::string artistName() { return _artistName; }
    std::string title() { return _title; }
    std::string albumName() { return _albumName; }
    unsigned albumID() { return _albumID; }
    std::string duration() { return _duration; }
    std::string position() { return _position; }

    void print();
    void parseFromJSONstream(std::fstream &stream);
    std::string htmlString();

private:
    std::string _artistName, _title, _albumName, _duration, _position;
    unsigned _albumID;

    // Private Functions
    void readJSONDataItem(std::fstream &stream);
};