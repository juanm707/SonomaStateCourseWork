#include "Set.hpp"
#include "SetScore.hpp"
#include "Game.hpp"
#include "GameScore.hpp"
#include "TieBreaker.hpp"

Set::Set( Player *p1, Player *p2 ): Competition( p1, p2 ) {}

Score *Set::play( Player *p ) {
    SetScore *score = new SetScore( player1(), player2() );
    Game *game = new Game( player1(), player2());

    while ( !score->haveAWinner() ) {
        if (score->shouldPlayATieBreaker()) {
            TieBreaker *t = new TieBreaker( player1(), player2() );
            TieBreakerScore *tie = reinterpret_cast<TieBreakerScore *>( t->play(p) );
            score->addTieScore(tie);
            return score;
        }
        GameScore *gameScore = reinterpret_cast<GameScore *>( game->play( p ));
        score->addScore(gameScore->getWinner());
        delete gameScore;
        p = Player::otherPlayer(p); // Alternate game serves
    }
    return score;
}

