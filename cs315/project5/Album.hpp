/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#ifndef PROJECT5_ALBUM_H
#define PROJECT5_ALBUM_H

#include <string>
#include "JSONDataObject.hpp"
#include "Tracks.hpp"
#include "AlbumImage.hpp"
//#include "Artist.hpp"

class Artist;

class Album: public JSONDataObject {
public:

    Album(): cachedTitle(false), cachedGenres(false), cachedAlbumID(false), cachedArtistID(false), cachedNumImages(false),
             cachedNumTracks(false), cachedYear(false), _primaryAlbumImage(new AlbumImage()), _secondaryAlbumImage(new AlbumImage()) {}

    ~Album();

    std::string title();
    std::string genres();
    unsigned albumID();
    unsigned artistID();
    unsigned numImages();
    unsigned numTracks();
    std::string year();

    void setTracks(Tracks *tracks) { _tracks = tracks; }
    void setArtist(Artist *artist) { _artist = artist; }

    Artist *artist() { return _artist; }
    Tracks *tracks()  { return _tracks; }

    void setPrimaryImage( AlbumImage * primaryImage ) { _primaryAlbumImage = primaryImage; }
    void setSecondaryImage( AlbumImage * secondaryImage ) { _secondaryAlbumImage = secondaryImage; }

    AlbumImage * primaryImage() { return _primaryAlbumImage;   }
    AlbumImage * secondaryImage()  { return _secondaryAlbumImage; }

    void print();
    std::string htmlString();

private:

    std::string _title, _genres, _year;
    unsigned _albumID, _artistID, _numImages, _numTracks;

    bool cachedTitle, cachedGenres, cachedAlbumID, cachedArtistID, cachedNumImages, cachedNumTracks, cachedYear;

    AlbumImage * _primaryAlbumImage, * _secondaryAlbumImage;
    Tracks * _tracks;
    Artist * _artist;

};

#endif //PROJECT5_ALBUM_H
