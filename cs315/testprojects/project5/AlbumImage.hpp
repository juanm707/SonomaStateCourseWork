/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#ifndef PROJECT5_ALBUMIMAGE_H
#define PROJECT5_ALBUMIMAGE_H

#include "JSONDataObject.hpp"

class AlbumImage: public JSONDataObject {
public:

    AlbumImage(): cachedHeight(false), cachedWidth(false), cachedAlbumID(false), cachedUri(false), cachedType(false), _type("n/a") {}
    ~AlbumImage();

    unsigned height();
    std::string uri();
    unsigned albumID();
    unsigned width();
    std::string type();

    std::string htmlString();
    void print();


private:

    unsigned _height, _width, _albumID;
    std::string _uri, _type;

    bool cachedHeight, cachedWidth, cachedAlbumID, cachedUri, cachedType;

};


#endif //PROJECT5_ALBUMIMAGE_H
