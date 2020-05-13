/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 4
*/

#include "Artist.hpp"
#include <iostream>
#include <sstream>

void Artist::print() {

    std::cout << _name << ' ' << _realName << ' ' << _profile
              << ' ' << _numImages << ' ' << _artistID << std::endl;
}

void Artist::parseFromJSONstream(std::fstream &stream) {

    char c;

    if( !(stream >> c) || c != '{' ) { // The first non-space character of a JSON object has to be '{'.
        // print some error message and exit the program.
        std::cerr << "Expected {\n";
        exit(3);
    }

    do {
        readJSONDataItem(stream);   // we know that a JSON object has at least one JSON key/value pair.
        // readJSONDataItem reads exactly one such pair.
        stream >> c;  // the character after the JSON key/value pair is either a comma, indicating
        // there are more key/value pairs to be read, or a closed-brace ('}').
        // A closed-brace means that we have already read all JSON key/value pairs.
    } while( c != '}' );
}

std::string Artist::htmlString() {

    std::stringstream html;

    html << "\t<li><p>" << _name << "</p>\n";
    html << "\t\t<ul style=\"list-style-type:none\">\n";
    html << "\t\t\t<li><p><b>Artist_name: </b><font color=\"blue\"> " << _name << "</font></p></li>\n";
    html << "\t\t\t<li><p><b>Real_name: </b><font color=\"blue\">" << _realName << "</font></p></li>\n";
    html << "\t\t\t<li><p><b>ID: </b><font color=\"blue\">" << _artistID << "</font></p></li>\n";
    html << "\t\t\t<li><p><b>Number of images: </b><font color=\"blue\">" << _numImages << "</font></p></li>\n";
    html << "\t\t\t<li><p><b>Profile: </b><font color=\"blue\">" << _profile << "</font></p></li>\n";
    html << "\t\t</ul>\n";
    html << "\t</li>\n";
    return html.str();
}

// Private functions

void Artist::readJSONDataItem(std::fstream &stream)
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
        if (key == "artist_id")
            _artistID = number;
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

                else if (c == 'u')
                    value += "";

                else if (c == 'U')
                    value += "";

                //value += c;
                stream.get(c);
            }

            else {
                value += c;
                stream.get(c);
            }
        }

        if (key == "artist_name")
            _name = value;
        else if (key == "real_name")
            _realName = value;
        else if (key == "profile")
            _profile = value;
        else if (key == "num_images") {
            _numImages = std::atoi(value.c_str());
        }
    }
}