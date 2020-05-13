#ifndef _Set_hpp
#define _Set_hpp

#include "Competition.hpp"

/**  A Set is a Competition in which players play several games until
 *  there is a winner.  The rule of winning a set is given by class,
 *  SetScore.  The argument to method "play" specifies the player who
 *  serves the points of the first game.  After that, players
 *  alternate who serves the next game. 
 */

class Set: public Competition {
public: 
  Set( Player *p1, Player *p2 );
  Score *play( Player *p );
};

#endif
