#include <iostream>
#include "MatchScore.hpp"

MatchScore::MatchScore( Player *p1, Player *p2 ): Score( p1, p2 ), setNumber(0) {}

bool MatchScore::haveAWinner()  {
    return p1Score == 3 || p2Score == 3;
}
void MatchScore::addScore( Score *score ) {
    Player *p = score->getWinner();
    p == player1() ? p1Score++ : p2Score++;
    scores[setNumber] = reinterpret_cast<SetScore *>(score);
    setNumber++;
}

void MatchScore::print() {
    for( int i = 0; i < setNumber; i++ ) {
        std::cout << "      " << i+1;
        scores[i]->print();
    }
}
MatchScore::~MatchScore() {
    for( int i = 0; i < setNumber; i++ )
      delete scores[i];
}
