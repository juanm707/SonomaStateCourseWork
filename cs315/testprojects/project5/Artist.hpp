/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#ifndef PROJECT5_ARTIST_H
#define PROJECT5_ARTIST_H

#include <string>
#include "Albums.hpp"
#include "JSONDataObject.hpp"
#include "ArtistImage.hpp"


class Artist: public JSONDataObject {
public:

    Artist(): cachedName(false), cachedRealName(false), cachedProfile(false), cachedNumImages(false),
              cachedArtistID(false), _primaryImage(new ArtistImage()), _secondaryImage(new ArtistImage()) {}

    ~Artist();

    std::string profile();
    std::string artistName();
    std::string realName();
    std::string numImages();  // since it's a string in the JSON file
    unsigned    artistID();

    void        print();
    std::string htmlString();

    // the following 4 function-prototypes are new to this project.
    void setAlbums(Albums *albums) { _albums = albums; }
    Albums *albums() { return _albums; }

    void setPrimaryImage( ArtistImage * primaryImage ) { _primaryImage = primaryImage; }
    void setSecondaryImage( ArtistImage * secondaryImage ) { _secondaryImage = secondaryImage; }

    ArtistImage *primaryImage()       { return _primaryImage;   }
    ArtistImage *secondaryImage()     { return _secondaryImage; }

private:

    std::string _name, _realName, _profile, _numImages;
    unsigned _artistID;

    bool cachedName, cachedRealName, cachedProfile, cachedNumImages, cachedArtistID;

    // the following 3 variables are new to this project.

    ArtistImage *_primaryImage, *_secondaryImage;
    Albums *_albums;
};

#endif //PROJECT5_ARTIST_H
