/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Lab 4
*/

#include<iostream>
#include "SetScore.hpp"
#include <cmath>

SetScore::SetScore( Player *p1, Player *p2 ): Score(p1, p2), tieScore(0) {}
  
bool SetScore::haveAWinner()           {

  return (( p1Score >= 6 || p2Score >= 6 ) && std::abs( p1Score - p2Score ) >= 2) || tieScore != NULL;

}
bool SetScore::shouldPlayATieBreaker() {
    return player1Score() == 6 && player2Score() == 6;
}

void SetScore::addTieScore( TieBreakerScore *score ) {
    addScore( score->getWinner() );
    this->tieScore = score;
}

void SetScore::print() {
  std::cout << "\t " << player1Score() << "\t     " << player2Score();
    if( tieScore != NULL )
      tieScore->print();
    else
        std::cout << std::endl;
}
