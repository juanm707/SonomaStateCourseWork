#ifndef _Game_hpp
#define _Game_hpp

#include "Competition.hpp"

/**  A Game is a Competition in which a player (specified by the
 *  argument to "play") serves points until there is a winner.  The
 *  rule of winning a game is given by class, GameScore.
 */

class Game: public Competition {
public:
  Game( Player *p1, Player *p2 );
  Score *play( Player *p );
};

#endif
