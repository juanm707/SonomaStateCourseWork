#ifndef PARSETOOLS_H
#define PARSETOOLS_H

// Parse a command line into a list of words,
//    separated by whitespace.
// Returns the number of words
//
int split_cmd_line(char* line, char** list_to_populate); 

#endif
