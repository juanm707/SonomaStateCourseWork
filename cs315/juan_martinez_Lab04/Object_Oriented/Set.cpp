/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Lab 4
*/

#include "Set.hpp"
#include "SetScore.hpp"
#include "GameScore.hpp"
#include "Game.hpp"
#include "TieBreaker.hpp"

Set::Set( Player *p1, Player *p2 ): Competition( p1, p2 ) {}

Score *Set::play( Player *p ) {
    SetScore * score = new SetScore( player1(), player2() );

    while ( !score->haveAWinner() ) {
        Game * otherGame = new Game( player1(), player2() );
        GameScore * gameScore = reinterpret_cast<GameScore *>( otherGame->play(p));
        score->addScore( gameScore->getWinner() );
        p == player1() ? p = player2() : p = player1();
        delete gameScore;
        delete otherGame;
        if (score->shouldPlayATieBreaker()) {

            TieBreaker * tieBreaker = new TieBreaker( player1(), player2() );
            TieBreakerScore * tieScore = reinterpret_cast<TieBreakerScore *>( tieBreaker->play(p));
            score->addTieScore(tieScore);
        }

    }
    return score;
}

