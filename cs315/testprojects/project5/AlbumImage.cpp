/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#include <iostream>
#include <sstream>
#include "AlbumImage.hpp"

AlbumImage::~AlbumImage() {

}

std::string AlbumImage::htmlString() {

    std::stringstream html;

    html << "<img src=";
    html << uri();
    html << " style=\"width:";
    html << width()/2.1;
    html << "px;height:";
    html << height()/2.1;
    html << "px;\">";

    return html.str();
}

unsigned AlbumImage::height() {

    if (cachedHeight)
        return _height;
    cachedHeight = true;
    return _height = valueForIntegerAttribute("height");
}

std::string AlbumImage::uri() {

    if (cachedUri)
        return _uri;
    cachedUri = true;
    return _uri = valueForStringAttribute("uri");
}

unsigned AlbumImage::albumID() {

    if (cachedAlbumID)
        return _albumID;
    cachedAlbumID = true;
    return _albumID = valueForIntegerAttribute("album_id");
}

unsigned AlbumImage::width() {

    if (cachedWidth)
        return _width;
    cachedWidth = true;
    return _width = valueForIntegerAttribute("width");
}

std::string AlbumImage::type() {

    if (cachedType)
        return _type;
    cachedType = true;
    return _type = valueForStringAttribute("type");
}

void AlbumImage::print() {

    std::cout << _height << ' ' << _width << ' ' << _albumID << ' ' << _uri << ' ' << _type << std::endl;
}
