/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#ifndef PROJECT5_ARTISTS_H
#define PROJECT5_ARTISTS_H

#include <vector>
#include "JSONArray.hpp"
#include "Artist.hpp"
#include "JSONDataObject.hpp"
#include "Albums.hpp"
#include "ArtistImages.hpp"

class Artists: public JSONArray
{
public:
    Artists();
    ~Artists();

    int numArtists() { return _listOfDataObjects->size(); }
    void addArtist(Artist *artist) { _listOfDataObjects->push_back(artist); }

    Artist *artistWithID(unsigned int aID);

    void loadArtistsFromFile(std::string fileName);

    //std::string htmlString();

    JSONDataObject *jsonObjectNode() { return new Artist();  }

    void setAlbumsForArtists(Albums *albums);

    void setImagesForArtists(ArtistImages * artistImages);

    std::vector<Artist *> *listOfArtists() { return (std::vector<Artist *> *) _listOfDataObjects; }

    //void runAsserts();  // used for checking the integrity of this class. UNCOMMENT

};

#endif //PROJECT5_ARTISTS_H
