#include<iostream>
#include "SetScore.hpp"

SetScore::SetScore( Player *p1, Player *p2 ): Score(p1, p2), tieScore(0) {}
  
bool SetScore::haveAWinner() {
    return (abs(p1Score - p2Score) >= 2) && (p1Score >= 6 || p2Score >= 6);
}

bool SetScore::shouldPlayATieBreaker() {
    return (p1Score == 6) && (p2Score == 6);
}

void SetScore::addTieScore( TieBreakerScore *score ) {
    addScore( score->getWinner() );
    this->tieScore = score;
}

void SetScore::print() {
    std::cout << "         " << player1Score() << "                 " << player2Score();
    if( tieScore != NULL )
      tieScore->print();
    else
        std::cout << '\n';
}
