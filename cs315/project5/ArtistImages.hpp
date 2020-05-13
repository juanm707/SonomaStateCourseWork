/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#ifndef PROJECT5_ARTISTIMAGES_H
#define PROJECT5_ARTISTIMAGES_H


#include "JSONArray.hpp"
#include "ArtistImage.hpp"

class ArtistImages: public JSONArray {

public:
    ArtistImages();
    ~ArtistImages();

    int numArtistImages() { return _listOfDataObjects->size(); }

    void addArtistImage(ArtistImage *artistImage) { _listOfDataObjects->push_back(artistImage); }

    void loadArtistImagesFromFile(std::string artistImagefileName);

    //std::string htmlString();

    JSONDataObject *jsonObjectNode() { return new ArtistImage();  }

    std::vector<ArtistImage *> *listOfArtistImages() { return (std::vector<ArtistImage *> *) _listOfDataObjects; }

    //void runAsserts();  // used for checking the integrity of this class. UNCOMMENT

};


#endif //PROJECT5_ARTISTIMAGES_H
