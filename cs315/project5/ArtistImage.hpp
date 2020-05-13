/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#ifndef PROJECT5_ARTISTIMAGE_H
#define PROJECT5_ARTISTIMAGE_H

#include "JSONDataObject.hpp"

class ArtistImage: public JSONDataObject {
public:

    ArtistImage(): cachedHeight(false), cachedWidth(false), cachedArtistID(false), cachedUri(false), cachedType(false), _type("n/a") {}
    ~ArtistImage();

    unsigned height();
    std::string uri();
    unsigned artistID();
    unsigned width();
    std::string type();

    std::string htmlString();
    void print();

private:

    unsigned _height, _width, _artistID;
    std::string _uri, _type;

    bool cachedHeight, cachedWidth, cachedArtistID, cachedUri, cachedType;
};


#endif //PROJECT5_ARTISTIMAGE_H
