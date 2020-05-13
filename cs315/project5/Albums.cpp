/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#include <iostream>
#include "Albums.hpp"

Albums::Albums() {

}

Albums::~Albums() {

}

Album * Albums::albumWithID(unsigned int aID) {

    for (auto albumItem: *_listOfDataObjects) {
        if (albumItem->valueForIntegerAttribute("album_id") == aID) {
            return (Album *)albumItem;
        }
    }

    return nullptr;
}

void Albums::setTracksForAlbums(Tracks *tracks) {

    for (auto albumItem: *_listOfDataObjects) {
        Album * thisAlbum = (Album *)albumItem;

        Tracks * tracksForAlbum = new Tracks();
        for (auto trackItem: *tracks->listOfTracks()) {
            if (thisAlbum->albumID() == trackItem->valueForIntegerAttribute("album_id")) {
                tracksForAlbum->addTrack(trackItem);
            }
        }

        thisAlbum->setTracks(tracksForAlbum);
    }

}

void Albums::loadAlbumsFromFile(std::string albumFileName) {

    std::fstream albumStream;
    albumStream.open(albumFileName.c_str(), std::fstream::in);

    if (albumStream.fail()) {
        std::cerr << "Missing file: albums.json OR albums_human_readable.json\nTerminating...\n";
        exit(2);
    }

    parseJSONArray(albumStream);
    albumStream.close();

}

void Albums::setImagesForAlbums(AlbumImages *albumImages) {

    for (auto albumImageItem: *albumImages->listOfArtistImages()) {

        Album * thisAlbum = albumWithID(albumImageItem->albumID());

        if (albumImageItem->type() == "primary")
            thisAlbum->setPrimaryImage(albumImageItem);
        else if (albumImageItem->type() == "secondary")
            thisAlbum->setSecondaryImage(albumImageItem);
    }
}