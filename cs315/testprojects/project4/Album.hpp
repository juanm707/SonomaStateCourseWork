/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 4
*/

#include<fstream>
#include<cstring>

class Album
{
public:
    Album(): _title(""), _style(""), _albumID(0), _numVideos(0), _numTracks(0), _year(""), _numImages(0) {}
    ~Album();

    std::string title() { return _title; } //check
    std::string style() { return _style; } //check
    unsigned albumID()  { return _albumID; } //check
    unsigned numVideos(){ return _numVideos; } // DO WE USE THIS ONE????
    unsigned numImages(){ return _numImages; } //check
    unsigned numTracks(){ return _numTracks; } //check
    std::string year() { return _year; } //check

    void print();
    void parseFromJSONstream(std::fstream &stream);
    std::string htmlString();

private:
    std::string _title, _style, _year;
    unsigned _albumID, _numVideos, _numTracks, _numImages;

    // Private Functions
    void readJSONDataItem(std::fstream &stream);
};