/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#include <iostream>
#include <sstream>
#include "Artist.hpp"
#include "Album.hpp"

Album::~Album() {


}

std::string Album::htmlString() {

    std::stringstream html;

    html << "\t<h3>" << title() << "</h3>\n";

    // CHECK IMAGES
    if (primaryImage()->type() != "n/a")
        html << primaryImage()->htmlString();
    else if (secondaryImage()->type() != "n/a")
        html << secondaryImage()->htmlString();
    // END CHECK IMAGES

    html << "\t\t\t\n<h2>" << title() << "</h2>\n";
    html << "\t\t\t<p>Artist: <font color=\"blue\">" << artist()->artistName() << "</font></p>\n";
    html << "\t\t\t<p>Genres: <font color=\"blue\">" << genres() << "</font></p>\n";
    html << "\t\t\t<p>Year: <font color=\"blue\">" << year() << "</font></p>\n";

    return html.str();
}

std::string Album::title() {

    if (cachedTitle)
        return _title;
    cachedTitle = true;
    return _title = valueForStringAttribute("title");

}

std::string Album::genres() {

    if (cachedGenres)
        return _genres;
    cachedGenres = true;
    return _genres = valueForStringAttribute("genres");

}

unsigned Album::albumID() {

    if (cachedAlbumID)
        return _albumID;
    cachedAlbumID = true;
    return _albumID = valueForIntegerAttribute("album_id");

}

unsigned Album::artistID() {

    if (cachedArtistID)
        return _artistID;
    cachedArtistID = true;
    return _artistID = valueForIntegerAttribute("artist_id");

}

unsigned Album::numImages() {

    if (cachedNumImages)
        return _numImages;
    cachedNumImages = true;
    return _numImages = valueForIntegerAttribute("num_images");

}

unsigned Album::numTracks() {

    if (cachedNumTracks)
        return _numTracks;
    cachedNumTracks = true;
    return _numTracks = valueForIntegerAttribute("num_tracks");
}

std::string Album::year() {

    if (cachedYear)
        return _year;
    cachedYear = true;
    return _year = valueForStringAttribute("year");

}

void Album::print() {

    std::cout << _title << ' ' << _genres << ' ' << _year << ' '
              << _albumID << ' ' << _artistID << ' ' << _numImages << ' ' << _numTracks << std::endl;
}