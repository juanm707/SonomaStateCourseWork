/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#include "Artists.hpp"
#include <iostream>

Artists::Artists() {

}

Artists::~Artists() {

}

Artist * Artists::artistWithID(unsigned int aID) {

    for (auto artistItem: *_listOfDataObjects) {
        if (artistItem->valueForIntegerAttribute("artist_id") == aID) {
            return (Artist *)artistItem;
        }
    }

    return nullptr;
}

void Artists::setAlbumsForArtists(Albums *albums) {

    for (auto artistItem: *_listOfDataObjects) {

        Albums * albumsForArtist = new Albums();
        for (auto albumItem: *albums->listOfAlbums()) {
            if (albumItem->artistID() == artistItem->valueForIntegerAttribute("artist_id")) {
                albumsForArtist->addAlbum(albumItem);
                albumItem->setArtist((Artist *)artistItem);
            }
        }
        Artist * artist = (Artist *)artistItem;
        artist->setAlbums(albumsForArtist);
    }
}

void Artists::loadArtistsFromFile(std::string artistsFileName)
{
    std::fstream artStream;
    artStream.open(artistsFileName.c_str(), std::fstream::in);

    if (artStream.fail()) {
        std::cerr << "Missing file: artists.json OR artists_human_readable.json\nTerminating...\n";
        exit(1);
    }

    parseJSONArray(artStream);
    artStream.close();
}

void Artists::setImagesForArtists(ArtistImages * artistImages) {

    for (auto artistImageItem: *artistImages->listOfArtistImages()) {

        Artist * thisArtist = artistWithID(artistImageItem->artistID());
        if (artistImageItem->type() == "primary")
            thisArtist->setPrimaryImage(artistImageItem);
        else if (artistImageItem->type() == "secondary")
            thisArtist->setSecondaryImage(artistImageItem);
    }
}
