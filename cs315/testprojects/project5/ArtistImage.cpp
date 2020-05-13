/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#include <sstream>
#include <iostream>
#include "ArtistImage.hpp"

ArtistImage::~ArtistImage() {

}

std::string ArtistImage::htmlString() {

    std::stringstream html;

    html << "<img src=";
    html << uri();
    html << " style=\";width:";
    html << width()/1.5;
    html << "px;height:";
    html << height()/1.5;
    html << "px;\">";

    return html.str();
}

unsigned ArtistImage::height() {

    if (cachedHeight)
        return _height;
    cachedHeight = true;
    return _height = valueForIntegerAttribute("height");
}

std::string ArtistImage::uri() {

    if (cachedUri)
        return _uri;
    cachedUri = true;
    return _uri = valueForStringAttribute("uri");
}

unsigned ArtistImage::artistID() {

    if (cachedArtistID)
        return _artistID;
    cachedArtistID = true;
    return _artistID = valueForIntegerAttribute("artist_id");
}

unsigned ArtistImage::width() {

    if (cachedWidth)
        return _width;
    cachedWidth = true;
    return _width = valueForIntegerAttribute("width");
}

std::string ArtistImage::type() {

    if (cachedType)
        return _type;
    cachedType = true;
    return _type = valueForStringAttribute("type");
}

void ArtistImage::print() {

    std::cout << _height << ' ' << _width << ' ' << _artistID << ' ' << _uri << ' ' << _type << std::endl;
}