/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Lab 4
*/

#include "TieBreaker.hpp"
#include "Game.hpp"
#include "GameScore.hpp"
#include "TieBreakerScore.hpp"
#include "PointScore.hpp"

TieBreaker::TieBreaker( Player *p1, Player *p2 ): Competition( p1, p2 ) {}
Score *TieBreaker::play( Player *p ) {

    TieBreakerScore * tieScore = new TieBreakerScore( player1(), player2() );
    int count = 0;

    while ( !tieScore->haveAWinner()) {
        PointScore * pointScore = reinterpret_cast<PointScore *>( p->serveAPoint() );
        tieScore->addScore( pointScore->getWinner() );
        delete pointScore;
       
        if (count++ % 2 == 0)
            p == player1() ? p = player2() : p = player1();
    }

    return tieScore;
}

