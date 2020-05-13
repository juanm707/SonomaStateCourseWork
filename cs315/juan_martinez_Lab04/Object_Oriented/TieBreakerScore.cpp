/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Lab 4
*/

#include "TieBreakerScore.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>

TieBreakerScore::TieBreakerScore( Player *p1, Player *p2 ): Score(p1, p2) {}

bool TieBreakerScore::haveAWinner() {
    return ( p1Score >= 7 || p2Score >= 7) && fabs( p1Score - p2Score ) >= 2;
}

void TieBreakerScore::print() {

    std::cout << std::setw(16) << "(tie breaker  " << player1Score() << "-" << player2Score() << ")\n";
}