#include<iostream>
#include <unistd.h>
#include <stdlib.h>
#include "GameScore.hpp"

GameScore::GameScore( Player *p1, Player *p2 ): Score( p1, p2 ) {}
    
bool GameScore::haveAWinner() {
   return ( p1Score >= 4 || p2Score >= 4 ) && abs( p1Score - p2Score ) >= 2;
}

void GameScore::print() {
  std::cout <<  "GameScore...   printing begins" << std::endl;
  std::cout <<  "p1 score = " << player1Score() << "\np2 Score = " << player2Score() << std::endl;
  std::cout <<  "GameScore...   printing ends" << std::endl;
}
