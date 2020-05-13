/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 4
*/

#include "Album.hpp"
#include <iostream>
#include <sstream>

void Album::print() {
    std::cout << _albumID << ' ' << _numTracks << ' ' << _year << ' '
              << _style << ' ' << _numImages << ' ' << _title << std::endl;
}

void Album::parseFromJSONstream(std::fstream &stream) {

    char c;

    if( !(stream >> c) || c != '{' ) { // The first non-space character of a JSON object has to be '{'.
        // print some error message and exit the program.
        std::cerr << "Expected {\n";
        exit(6);
    }

    do {
        readJSONDataItem(stream);   // we know that a JSON object has at least one JSON key/value pair.
        // readJSONDataItem reads exactly one such pair.
        stream >> c;  // the character after the JSON key/value pair is either a comma, indicating
        // there are more key/value pairs to be read, or a closed-brace ('}').
        // A closed-brace means that we have already read all JSON key/value pairs.
    } while( c != '}' );


}

std::string Album::htmlString() {

    std::stringstream html;

    html << "\t<li><p>" << _title << "</p>\n";
    html << "\t\t<ul style=\"list-style-type:none\">\n";
    html << "\t\t\t<li><p><b>Album_title: </b><font color=\"blue\"> " << _title << "</font></p></li>\n";
    html << "\t\t\t<li><p><b>Album_ID: </b><font color=\"blue\">" << _albumID << "</font></p></li>\n";
    html << "\t\t\t<li><p><b>Genre/Style: </b><font color=\"blue\">" << _style << "</font></p></li>\n";
    html << "\t\t\t<li><p><b>Number of videos: </b><font color=\"blue\">" << _numImages << "</font></p></li>\n";
    html << "\t\t\t<li><p><b>Number of tracks: </b><font color=\"blue\">" << _numTracks << "</font></p></li>\n";
    html << "\t\t\t<li><p><b>Year_recorded: </b><font color=\"blue\">" << _year << "</font></p></li>\n";
    html << "\t\t</ul>\n";
    html << "\t</li>\n";
    return html.str();

}

// Private Function

void Album::readJSONDataItem(std::fstream &stream)
{
    char c;
    if( !(stream >> c) || c != '"' ) { // The first non-space character of a JSON key/value pair has to be
        // a double-quote.
        // print some error message and exit the program.
        std::cerr << "Expected \"\n";
        exit(4);
    }

    // using stream.get(c) read one character at a time until you find the matching end double-quote.
    std::string key = "";
    stream >> c;

    while ( c != '"') {
        key += c;
        stream >> c;
    }

    // Notice that \" doesn't end the key string; it should be injected into the text of the key string.

    // After having read the key, including the closing double-quote, we should find a colon.
    if( !(stream >> c) || c != ':' ) {
        // print an error message and exit
        std::cerr << "Expected :\n";
        exit(5);
    }

    // Now, we are ready to read the value part. It is either a string or a number.
    stream >> c;

    if( isdigit(c)) {
        stream.unget(); // put the digit back into the stream so we read the number.
        int number;
        stream >> number;
        if (key == "album_id")
            _albumID = number;
        else if (key == "num_tracks")
            _numTracks = number;
        else if (key == "num_images")
            _numImages = number;
    }

    else {

        std::string value = "";
        //getline(stream,value);
        stream.get(c);
        // the value part is a string. Read it including the closing double-quotes.
        // Again, \" should be injected into the text of the value string.
        while ( c != '"') {

            if ( c == '\\') {
                //value += '\\';
                stream.get(c);
                if (c == 'n')
                    value += '\n';

                else if (c == 't')
                    value += '\t';

                else if (c == 'v')
                    value += '\v';

                else if (c == 'b')
                    value += '\b';

                else if (c == 'r')
                    value += '\r';

                else if (c == 'f')
                    value += '\f';

                else if (c == 'a')
                    value += '\a';

                else if (c == '?')
                    value += '\?';

                else if (c == '\'')
                    value += '\'';

                else if (c == '"')
                    value += '"';

                else if (c == '0')
                    value += '\0';

                else if (c == 'u') {
		  value += "";
                }

                else if (c == 'U')
                    value += "";

                stream.get(c);
            }

            else {
                value += c;
                stream.get(c);
            }
        }

        if (key == "year")
            _year = value;
        else if (key == "genres")
            _style = value;
        else if (key == "title")
            _title = value;
        //else if (key == "num_images") {
          //  _numImages = std::atoi(value.c_str());
        //}
    }
}
