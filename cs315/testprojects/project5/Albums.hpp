/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#ifndef PROJECT5_ALBUMS_H
#define PROJECT5_ALBUMS_H

#include <vector>
#include "JSONArray.hpp"
#include "JSONDataObject.hpp"
#include "Album.hpp"
#include "AlbumImages.hpp"

class Albums: public JSONArray
{
public:
    Albums();
    ~Albums();

    int numAlbums() { return _listOfDataObjects->size(); }
    void addAlbum(Album *album) { _listOfDataObjects->push_back(album); }

    Album *albumWithID(unsigned int aID);

    void loadAlbumsFromFile(std::string albumFileName);

    //std::string htmlString();

    JSONDataObject *jsonObjectNode() { return new Album();  }

    void setTracksForAlbums(Tracks *tracks);

    void setImagesForAlbums(AlbumImages *albumImages);

    std::vector<Album *> *listOfAlbums() { return (std::vector<Album *> *) _listOfDataObjects; }

    //void runAsserts();  // used for checking the integrity of this class.
};

#endif //PROJECT5_ALBUMS_H
