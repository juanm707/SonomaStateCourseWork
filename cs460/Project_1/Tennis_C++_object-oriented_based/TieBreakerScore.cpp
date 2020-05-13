#include<iostream>
#include <unistd.h>
#include <stdlib.h>
#include "TieBreakerScore.hpp"

TieBreakerScore::TieBreakerScore( Player *p1, Player *p2 ): Score(p1, p2) {}

bool TieBreakerScore::haveAWinner() {
    return ( p1Score >= 7 || p2Score >= 7 ) && abs( p1Score - p2Score ) >= 2;
}

void TieBreakerScore::print() {
    std::cout << "  (tie breaker  " << player1Score() << '-' << player2Score() << ")\n";
}