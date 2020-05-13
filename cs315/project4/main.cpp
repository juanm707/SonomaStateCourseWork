/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 4
*/

#include <iostream>
#include <vector>
#include "Artist.hpp"
#include "Album.hpp"
#include "Track.hpp"

//Function Prototypes

template <class T>
void readJSONArray(std::fstream &stream, std::vector <T *> & typeVec);

template <class T>
void HTML_OUTPUT(std::fstream & stream, std::ofstream & outPutStream, std::fstream & templateStream, std::vector <T *> & typeVec);

int main() {

    std::vector<Artist *> artistVec;
    std::vector<Album *> albumVec;
    std::vector<Track *> trackVec;

    // ARTIST //
    std::fstream artist_infile;
    artist_infile.open("./artists.json");
    if (artist_infile.fail()) {
        std::cerr << "Unable to open artists.json... Exiting!\n";
        exit(1);
    }

    std::ofstream artist_out;
    artist_out.open("./artists.html");

    std::fstream artist_template;
    artist_template.open("./artists_template.html");
    if (artist_template.fail()) {
        std::cerr << "Unable to open artists_template.html... Exiting!\n";
        exit(2);
    }
    // END ARTIST //

    // ALBUM //
    std::fstream album_infile;
    album_infile.open("./albums.json");
    if (album_infile.fail()) {
        std::cerr << "Unable to open albums.json... Exiting!\n";
        exit(3);
    }

    std::ofstream album_out;
    album_out.open("./albums.html");

    std::fstream album_template;
    album_template.open("./albums_template.html");
    if (album_template.fail()) {
        std::cerr << "Unable to open albums_template.html... Exiting!\n";
        exit(4);
    }
    // END ALBUM

    // TRACK //
    std::fstream track_infile;
    track_infile.open("./tracks.json");
    if (track_infile.fail()) {
        std::cerr << "Unable to open tracks.json... Exiting!\n";
        exit(5);
    }

    std::ofstream track_out;
    track_out.open("./tracks.html");

    std::fstream track_template;
    track_template.open("./tracks_template.html");
    if (track_template.fail()) {
        std::cerr << "Unable to open tracks_template.hmtl... Exiting!\n";
        exit(6);
    }
    // END TRACK //


    // ARTIST HTML
    HTML_OUTPUT(artist_infile, artist_out, artist_template, artistVec);

    // ALBUM HTML
    HTML_OUTPUT(album_infile, album_out, album_template, albumVec);

    // TRACK HTML
    HTML_OUTPUT(track_infile, track_out, track_template, trackVec);

    std::cout << "Created the following files: albums.html artists.html tracks.html\n";
    return 0;
}

//Implementation

template <class T>
void readJSONArray(std::fstream &stream, std::vector <T *> & typeVec)
{
    // The caller has opened the input file and has passed its stream to this function.
    // No input has been read from the stream yet.
    char c;

    if( !(stream >> c) || c != '[' ) {// the first non-space character is expected to be '['
        // print some error message and exit the program.
        std::cerr << "Expected {\n";
        exit(2);
    }
    do {

        T * typeT = new T();
        typeT->parseFromJSONstream(stream);// we know that a JSON array has at least one JSON object.
        typeVec.push_back(typeT);
        // readJSONDataObject reads that object, starting with '{'
        // and ending with '}'
        stream >> c;
        // the character after the JSON object is either a comma, indicating
        // there are more objects to be read, or a closed-bracket (']').
        // A closed-bracket means that we have already read all JSON objects.
        //delete artist;
    } while( c != ']' );
    return;
}

template <class T>
void HTML_OUTPUT(std::fstream & stream, std::ofstream & outPutStream, std::fstream & templateStream, std::vector <T *> & typeVec) {

    std::string html;

    // HMTL //
    std::getline(templateStream, html);

    while ( html != "{% artists %}" && html != "{% albums %}" && html != "{% tracks %}" ) {
        outPutStream << html;
        outPutStream << '\n';
        std::getline(templateStream, html);
    }

    outPutStream << "<ol>\n";

    readJSONArray(stream, typeVec);

    for ( auto & element : typeVec ) {
        outPutStream << element->htmlString() << std::endl;
    }

    outPutStream << "</ol>\n";
    outPutStream << "</body>\n</html>\n";
    // END HMTL //

    return;
}
