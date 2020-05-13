/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#include <iostream>
#include "AlbumImages.hpp"

AlbumImages::AlbumImages() {

}

AlbumImages::~AlbumImages() {

}

void AlbumImages::loadAlbumImagesFromFile(std::string albumImagefileName) {
    std::fstream artStream;
    artStream.open(albumImagefileName.c_str(), std::fstream::in);

    if (artStream.fail()) {
        std::cerr << "Missing file: albumImages.json OR album_images_human_readable.json\nTerminating...\n";
        exit(5);
    }

    parseJSONArray(artStream);
    artStream.close();
}
