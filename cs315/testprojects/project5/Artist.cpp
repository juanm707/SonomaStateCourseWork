/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#include "Artist.hpp"
#include <iostream>
#include <sstream>

Artist::~Artist() {


}

std::string Artist::htmlString() {

    std::stringstream html;

    html << "\t<h1>" << artistName() << "</h1>\n";

    // CHECK IMAGES
    if (primaryImage()->type() != "n/a")
        html << primaryImage()->htmlString();
    else if (secondaryImage()->type() != "n/a")
        html << secondaryImage()->htmlString();
    // END CHECK IMAGES

    html << "\n\t\t<ul style=\"list-style-type:none\">\n";
    html << "\t\t\t<li><p><b>Number of images: </b><font color=\"blue\">" << numImages() << "</font></p></li>\n";
    html << "\t\t\t<li><p><b>Profile: </b><font color=\"blue\">" << profile() << "</font></p></li>\n";
    html << "\t\t</ul>\n";

    return html.str();
}

std::string Artist::profile() {

    if( cachedProfile )
        return _profile;
    cachedProfile = true;
    return _profile = valueForStringAttribute("profile");

}

std::string Artist::artistName() {

    if ( cachedName )
        return _name;
    cachedName = true;
    return _name = valueForStringAttribute("artist_name");

}

std::string Artist::realName() {

    if (cachedRealName )
        return _realName;
    cachedRealName = true;
    return _realName = valueForStringAttribute("real_name");

}

std::string Artist::numImages() {

    if (cachedNumImages)
        return _numImages;
    cachedNumImages = true;
    return _numImages = valueForStringAttribute("num_images");

}

unsigned Artist::artistID() {

    if (cachedArtistID)
        return _artistID;
    cachedArtistID = true;
    return _artistID = valueForIntegerAttribute("artist_id");

}

void Artist::print() {
    std::cout << _name << ' ' << _realName << ' ' <<  _profile << ' '
              << _numImages << ' ' <<_artistID << std::endl;
}