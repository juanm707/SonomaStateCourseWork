#ifndef _Match_hpp
#define _Match_hpp

#include "Competition.hpp"
#include "Player.hpp"

/**  A Match is a Competition in which players play several sets until
 *  there is a winner.  The rule of winning a match is given by class,
 *  MatchScore.  The argument to method "play" specifies the player
 *  who serves the points of the first game of the first set of a
 *  match.  After that, players alternate who serves the next set.
 */

class Match: public Competition {

public: 
  Match( Player *p1, Player *p2 );
  Score *play( Player *p );
};

#endif
