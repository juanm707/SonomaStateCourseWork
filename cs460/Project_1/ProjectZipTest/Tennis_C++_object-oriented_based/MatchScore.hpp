#ifndef _MatchScore_hpp
#define _MatchScore_hpp

#include "Score.hpp"
#include "Player.hpp"
#include "SetScore.hpp"
#include "TieBreakerScore.hpp"

/**  A match is won by the player who wins the first 3 sets. 
 */

class MatchScore: public Score {

public: 
  MatchScore( Player *p1, Player *p2 );
  bool haveAWinner();
  void addScore( Score *score );
  void print();
  ~MatchScore();

private:
  SetScore *scores[5];
  int setNumber;
};

#endif
