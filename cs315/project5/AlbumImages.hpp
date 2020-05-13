/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#ifndef PROJECT5_ALBUMIMAGES_H
#define PROJECT5_ALBUMIMAGES_H


#include "JSONArray.hpp"
#include "AlbumImage.hpp"

class AlbumImages: public JSONArray {

public:

    AlbumImages();
    ~AlbumImages();

    int numAlbumImages() { return _listOfDataObjects->size(); }

    void addAlbumImage(AlbumImage *albumImage) { _listOfDataObjects->push_back(albumImage); }

    void loadAlbumImagesFromFile(std::string albumImagefileName);

    //std::string htmlString();

    JSONDataObject *jsonObjectNode() { return new AlbumImage();  }

    std::vector<AlbumImage *> *listOfArtistImages() { return (std::vector<AlbumImage *> *) _listOfDataObjects; }

    //void runAsserts();  // used for checking the integrity of this class.

};

#endif //PROJECT5_ALBUMIMAGES_H
