#include "Match.hpp"
#include "MatchScore.hpp"
#include "Set.hpp"

Match::Match( Player *p1, Player *p2 ): Competition( p1, p2 ) {}

Score *Match::play( Player *p ) {
    MatchScore *score = new MatchScore( player1(), player2() );
    Set *set = new Set( player1(), player2());

    while ( !score->haveAWinner() ) {
        SetScore *setScore = reinterpret_cast<SetScore *>( set->play( p ));
        score->addScore( setScore );
        p = Player::otherPlayer(p);  // Alternating set servers, switch servers after each set.
    }
    return score;
}
