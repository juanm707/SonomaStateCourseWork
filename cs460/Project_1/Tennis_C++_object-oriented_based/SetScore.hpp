#ifndef _SetScore_hpp
#define _SetScore_hpp

#include "Player.hpp"
#include "TieBreakerScore.hpp"

/**  The player who wins at least 6 games and is ahead by at least
 *  2 games wins a set.  A tie-breaker will be played is the players
 *  wins 6 games each.  In that case, the player who wins the
 *  tie-breaker wins the set. 
 */

class SetScore: public Score {

public: 
  SetScore( Player *p1, Player *p2 );
  bool haveAWinner();
  bool shouldPlayATieBreaker();
  void addTieScore( TieBreakerScore *score );
  void print();

private:
  TieBreakerScore *tieScore;
};

#endif
