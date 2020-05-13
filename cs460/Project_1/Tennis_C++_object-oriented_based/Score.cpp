#include "Score.hpp"

Score::Score( Player *player1, Player *player2 ): p1( player1 ), p2( player2 ) {
    p1Score = p2Score = 0;
}

Player *Score::player1()   { return p1; }
Player *Score::player2()   { return p2; }
int Score::player1Score()  { return p1Score; }
int Score::player2Score()  { return p2Score; }
Player *Score::getWinner() { return p1Score > p2Score ? player1() : player2(); }
bool Score::areTied()      { return p1Score == p2Score; }

void Score::addScore( Player *p ) {
  p == player1() ? p1Score++ : p2Score++;
}
