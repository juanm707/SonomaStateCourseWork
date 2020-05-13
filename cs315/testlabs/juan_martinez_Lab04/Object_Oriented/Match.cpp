/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Lab 4
*/

#include "Match.hpp"
#include "MatchScore.hpp"
#include "Set.hpp"

Match::Match( Player *p1, Player *p2 ): Competition( p1, p2 ) {}

Score *Match::play( Player *p ) {
    MatchScore * score = new MatchScore( player1(), player2() );

    while (!score->haveAWinner()) {
        Set * otherSet = new Set( player1(), player2() );
        SetScore * setScore = reinterpret_cast<SetScore *>( otherSet->play(p));
        score->addScore(setScore);
        p == player1() ? p = player2() : p = player1();
        //delete setScore;
       // delete score;
    }

    return score;
}
