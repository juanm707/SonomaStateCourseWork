/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#include <iostream>
#include "Tracks.hpp"

Tracks::Tracks() {

}

Tracks::~Tracks() {

}

void Tracks::loadTracksFromFile(std::string tracksFileName) {

    std::fstream trackStream;
    trackStream.open(tracksFileName.c_str(), std::fstream::in);

    if (trackStream.fail()) {
        std::cerr << "Missing file: tracks.json OR tracks_human_readable.json\nTerminating...\n";
        exit(3);
    }

    parseJSONArray(trackStream);
    trackStream.close();
}
