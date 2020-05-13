#ifndef _GameScore_hpp
#define _GameScore_hpp


#include "Score.hpp"
#include "Player.hpp"

/**  The player who scores at least 4 points and is ahead by at least
 *  2 points wins a game.
 */

class GameScore: public Score {

public:
  GameScore( Player *p1, Player *p2 );
  bool haveAWinner();
  void print();
};

#endif
