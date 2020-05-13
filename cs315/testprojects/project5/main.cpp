/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#include <iostream>
#include <fstream>
#include "Artists.hpp"

// FUNCTION PROTOTYPE
void HTMLMasterOutput (Artists* artistCollection); // Creates the master HTML file

int main() {

    // LOAD FILES
    Artists * artistCollection = new Artists();
    artistCollection->loadArtistsFromFile("./artists.json");

    Albums * albumCollection = new Albums();
    albumCollection->loadAlbumsFromFile("./albums.json");

    Tracks * trackCollection = new Tracks();
    trackCollection->loadTracksFromFile("./tracks.json");

    ArtistImages * artistImagesCollection = new ArtistImages();
    artistImagesCollection->loadArtistImagesFromFile("./artistImages.json");

    AlbumImages * albumImagesCollection = new AlbumImages();
    albumImagesCollection->loadAlbumImagesFromFile("./albumImages.json");

    // LINK ITEMS TOGETHER
    artistCollection->setImagesForArtists(artistImagesCollection);
    artistCollection->setAlbumsForArtists(albumCollection);
    albumCollection->setTracksForAlbums(trackCollection);
    albumCollection->setImagesForAlbums(albumImagesCollection);
    // END

    HTMLMasterOutput(artistCollection);

    std::cout << "Created the following: artists.html\n";
    std::cout << "Directory \"html_albums\" now has the HTML files of every album.\n";

    return 0;
}

// FUNCTION IMPLEMENTATION
void HTMLMasterOutput (Artists* artistCollection) {

    // MASTER OUTPUT
    std::ofstream htmlOutput;
    htmlOutput.open("./artists.html");

    htmlOutput << "<!DOCTYPE html>\n";
    htmlOutput << "<html>\n";
    htmlOutput << "<head>\n";
    htmlOutput << "<title>Artists</title>\n";
    htmlOutput << "</head>\n";
    htmlOutput << "<body>\n";

    for (auto artistElem: *artistCollection->listOfArtists()) {

        htmlOutput << artistElem->htmlString(); // Artist Info Output

        htmlOutput << "\t<h2>Albums</h2>\n";
        htmlOutput << "<ol>\n";

        for (auto albumElem: *artistElem->albums()->listOfAlbums()) {

            //TO CREATE FILE IN THE html_albums DIRECTORY... START
            std::string albumFile = std::to_string(albumElem->albumID()) + ".html";
            std::ofstream albumHtml;
            albumHtml.open("./html_albums/" + albumFile);
            albumHtml << "<!DOCTYPE html>\n";
            albumHtml << "<html>\n";
            albumHtml << "<head>\n";
            albumHtml << "<title>";
            albumHtml << albumElem->title();
            albumHtml << "</title>\n";
            albumHtml << "</head>\n";
            albumHtml << "<body>\n";
            albumHtml << albumElem->htmlString();
            // END

            htmlOutput << "<li>";
            htmlOutput << albumElem->htmlString();
            htmlOutput << "</li>";

            htmlOutput << "\t<h2>Tracklist</h2>\n";

            for (auto trackElem: *albumElem->tracks()->listOfTracks()) {

                albumHtml << trackElem->htmlString();

                htmlOutput << trackElem->htmlString();
            }

            albumHtml << "</body>\n";
            albumHtml << "</html>\n";
        }

        htmlOutput << "</ol>\n";
    }

    htmlOutput << "</body>\n";
    htmlOutput << "</html>\n";

}
