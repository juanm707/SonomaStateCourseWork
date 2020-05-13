/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#ifndef PROJECT5_TRACK_H
#define PROJECT5_TRACK_H

#include <string>
#include "JSONDataObject.hpp"

class Track: public JSONDataObject {
public:

    Track(): cachedArtistName(false), cachedTitle(false), cachedAlbumName(false), cachedDuration(false),
             cachedPosition(false), cachedAlbumID(false) {}

    ~Track();

    std::string artistName();
    std::string title();
    std::string albumName();
    std::string duration();
    std::string position();
    unsigned albumID();

    void print();
    std::string htmlString();

private:

    std::string _artistName, _title, _albumName, _duration, _position;
    unsigned _albumID;

    bool cachedArtistName, cachedTitle, cachedAlbumName, cachedDuration, cachedPosition, cachedAlbumID;

};

#endif //PROJECT5_TRACK_H
