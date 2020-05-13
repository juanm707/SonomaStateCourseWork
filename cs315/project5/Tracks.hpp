/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#ifndef PROJECT5_TRACKS_H
#define PROJECT5_TRACKS_H

#include <vector>
#include "JSONArray.hpp"
#include "Track.hpp"
#include "JSONDataObject.hpp"

class Tracks: public JSONArray
{
public:
    Tracks();
    ~Tracks();

    int numTracks() { return _listOfDataObjects->size(); }

    void addTrack(Track *track) { _listOfDataObjects->push_back(track); }

    void loadTracksFromFile(std::string tracksFileName);

    //std::string htmlString();

    JSONDataObject *jsonObjectNode() { return new Track();  }

    std::vector<Track *> *listOfTracks() { return (std::vector<Track *> *) _listOfDataObjects; }

    //void runAsserts();  // used for checking the integrity of this class.

};

#endif //PROJECT5_TRACKS_H
