#include "Game.hpp"
#include "Score.hpp"
#include "GameScore.hpp"
#include "PointScore.hpp"

Game::Game( Player *p1, Player *p2 ): Competition( p1, p2 ) {}

Score *Game::play( Player *p ) {
    GameScore *score = new GameScore( player1(), player2() );

    while( !score->haveAWinner() ) {
      PointScore *pointScore = reinterpret_cast<PointScore *>( p->serveAPoint() );
      score->addScore( pointScore->getWinner() );
      delete pointScore;
    }
    return score;
}

