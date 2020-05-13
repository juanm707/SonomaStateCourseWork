#include <iostream>
#include "PointScore.hpp"
#include "Player.hpp"

PointScore::PointScore( Player *p1, Player *p2 ): Score( p1, p2 ) {}
bool PointScore::haveAWinner() {
    return  p1Score == 1 || p2Score == 1;
}

void PointScore::print() {
  std::cout << "PointScore...   printing begins" << std::endl;
  std::cout << "p1 score = " << player1Score() << "\np2 Score = " << player2Score() << std::endl; 
  std::cout << "PointScore...   printing ends" << std::endl;
}
