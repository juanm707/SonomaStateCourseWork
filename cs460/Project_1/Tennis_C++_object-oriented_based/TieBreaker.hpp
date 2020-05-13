#ifndef _TieBreaker_hpp
#define _TieBreaker_hpp

#include "Competition.hpp"

/** A TieBreaker is a game with different rules for who serves the
 * points and the number of points required to win.  The player that
 * begins a tie-breaker plays the first point.  There after, starting
 * with the next player, each player serve two points in succession
 * and the players alternate who serves the points.
 */

class TieBreaker: public Competition {

public:
  TieBreaker( Player *p1, Player *p2 );
  Score *play( Player *p );
};

#endif
