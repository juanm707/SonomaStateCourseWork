/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

#include <iostream>
#include "JSONDataItem.hpp"

void JSONDataItem::parseJSONItem(std::fstream &stream) {

    char c;
    if (!(stream >> c) || c != '"') { // The first non-space character of a JSON key/value pair has to be
        // a double-quote.
        // print some error message and exit the program.
        std::cerr << "Expected \"\n";
        exit(4);
    }

    // using stream.get(c) read one character at a time until you find the matching end double-quote.

    //std::string key = "";
    _attribute = "";

    stream >> c;

    while (c != '"') {
        _attribute += c;
        stream >> c;
    }

    // Notice that \" doesn't end the key string; it should be injected into the text of the key string.

    // After having read the key, including the closing double-quote, we should find a colon.
    if (!(stream >> c) || c != ':') {
        // print an error message and exit
        std::cerr << "Expected :\n";
        exit(5);
    }

    // Now, we are ready to read the value part. It is either a string or a number.
    stream >> c;

    if (isdigit(c)) {
        _isNumber = true;
        stream.unget(); // put the digit back into the stream so we read the number.

        //int number;
        //stream >> number;

        stream >> _ivalue;
        hasReadAnItem = true;

        /*if (key == "artist_id")
            _artistID = number;
        else if (key == "num_images")
            _numImages = number;*/
    } else {

        //std::string value = "";

        stream.get(c);
        // the value part is a string. Read it including the closing double-quotes.
        // Again, \" should be injected into the text of the value string.

        while (c != '"') {

            if (c == '\\') {

                stream.get(c);
                if (c == 'n')
                    _svalue += '\n';

                else if (c == 't')
                    _svalue += '\t';

                else if (c == 'v')
                    _svalue += '\v';

                else if (c == 'b')
                    _svalue += '\b';

                else if (c == 'r')
                    _svalue += '\r';

                else if (c == 'f')
                    _svalue += '\f';

                else if (c == 'a')
                    _svalue += '\a';

                else if (c == '?')
                    _svalue += '\?';

                else if (c == '\'')
                    _svalue += '\'';

                else if (c == '"')
                    _svalue += '"';

                else if (c == '0')
                    _svalue += '\0';

                else if (c == 'u')
                    _svalue += "";

                else if (c == 'U')
                    _svalue += "";

                //value += c;
                stream.get(c);
            }

            else {
                _svalue += c;
                stream.get(c);
            }
        }

        hasReadAnItem = true;
    }
}