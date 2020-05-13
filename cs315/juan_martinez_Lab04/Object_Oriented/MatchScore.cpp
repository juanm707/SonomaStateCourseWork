/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Lab 4
*/

#include "MatchScore.hpp"
#include <iostream>

MatchScore::MatchScore( Player *p1, Player *p2 ): Score( p1, p2 ), setNumber(0) {}
bool MatchScore::haveAWinner()  { // just to make the compiler happy return false;
    return ( p1Score == 3 || p2Score == 3);
}
void MatchScore::addScore( Score *score ) {

    scores[setNumber] = reinterpret_cast<SetScore *>(score);
    setNumber++;
    score->getWinner() == player1() ? p1Score++ : p2Score++;
    return;
}

void MatchScore::print() {
    for( int i = 0; i < setNumber; i++ ) {
        std::cout << "\t" << i + 1;
        scores[i]->print();
    }
}
MatchScore::~MatchScore() {
    for( int i = 0; i < setNumber; i++ )
      delete scores[i];
}
