#ifndef _Score_hpp
#define _Score_hpp

/** Class, Score, represents the abstract notion of keeping track of
 *  numbers related to different types of competition.  These numbers
 *  are meaningful only within the context of competition for which
 *  the score is kept.  For example, if the value of method,
 *  player1Score() was 3 and the score was the representation of the
 *  result of a game, 3 refers to 3 points being won by Player1().
 *  On the other hand, if this score represented a set, then 3
 *  represents the number of sets won by Player1().
*/

class Player;

class Score {
public:
  Score( Player *player1, Player *player2 );
  Player *player1();
  Player *player2();
  int player1Score();
  int player2Score();
  Player *getWinner();
  bool areTied();
  void addScore( Player *p );

  virtual bool haveAWinner() = 0;
  virtual void print() = 0;

protected: 
  Player *p1, *p2;
  int p1Score, p2Score;
};

#endif
