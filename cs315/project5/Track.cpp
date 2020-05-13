/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#include "Track.hpp"
#include <iostream>
#include <sstream>

Track::~Track() {


}

std::string Track::htmlString() {

    std::stringstream html;

    html << "\t<p>" << title() << " " << duration() << "</p>\n";

    return html.str();

}

std::string Track::artistName() {

    if (cachedArtistName)
        return _artistName;
    cachedArtistName = true;
    return _artistName = valueForStringAttribute("artist_name");
}

std::string Track::title() {

    if (cachedTitle)
        return _title;
    cachedTitle = true;
    return _title = valueForStringAttribute("title");
}

std::string Track::albumName() {

    if (cachedAlbumName)
        return _albumName;
    cachedAlbumName = true;
    return _albumName = valueForStringAttribute("album_name");
}

std::string Track::duration() {

    if (cachedDuration)
        return _duration;
    cachedDuration = true;
    return _duration = valueForStringAttribute("duration");
}

std::string Track::position() {

    if (cachedPosition)
        return _position;
    cachedPosition = true;
    return _position = valueForStringAttribute("position");
}

unsigned Track::albumID() {

    if (cachedAlbumID)
        return _albumID;
    cachedAlbumID = true;
    return _albumID = valueForIntegerAttribute("album_id");
}

void Track::print() {

    std::cout << _artistName << ' ' << _title << ' ' << _albumName<< ' ' << _duration
    << ' ' << _position << ' ' << _albumID << std::endl;
}