#ifndef _TieBreakerScore_hpp
#define _TieBreakerScore_hpp

#include "Score.hpp"
#include "Player.hpp"

/**  The player who scores at least 7 points and is ahead by at least
 *  2 points wins a tie-breaker.
 */

class TieBreakerScore: public Score {
public:
  TieBreakerScore( Player *p1, Player *p2 );
  bool haveAWinner();
  void print();
};

#endif
