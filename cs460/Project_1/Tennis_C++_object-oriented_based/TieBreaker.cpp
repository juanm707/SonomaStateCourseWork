#include "TieBreaker.hpp"
#include "TieBreakerScore.hpp"
#include "PointScore.hpp"

TieBreaker::TieBreaker( Player *p1, Player *p2 ): Competition( p1, p2 ) {}

Score *TieBreaker::play( Player *p ) {
    bool firstServe = true;
    int serveCount = 0;

    TieBreakerScore *tieBS = new TieBreakerScore( player1(), player2());
    while( !tieBS->haveAWinner() ) {
        PointScore *pointScore = reinterpret_cast<PointScore *>( p->serveAPoint() );
        serveCount++;
        tieBS->addScore( pointScore->getWinner() );
        delete pointScore;
        if (firstServe) {
            p = Player::otherPlayer(p);
            firstServe = false;
            serveCount = 0;
        }
        if (serveCount == 2) {
            serveCount = 0;
            p = Player::otherPlayer(p);
        }
    }
    return tieBS;
}

