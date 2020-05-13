/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#include <iostream>
#include "ArtistImages.hpp"

ArtistImages::ArtistImages() {

}

ArtistImages::~ArtistImages() {

}

void ArtistImages::loadArtistImagesFromFile(std::string artistImagefileName) {
    std::fstream artStream;
    artStream.open(artistImagefileName.c_str(), std::fstream::in);

    if (artStream.fail()) {
        std::cerr << "Missing file: artistImages.json OR artists_images_human_readable.json\nTerminating...\n";
        exit(4);
    }

    parseJSONArray(artStream);
    artStream.close();
}