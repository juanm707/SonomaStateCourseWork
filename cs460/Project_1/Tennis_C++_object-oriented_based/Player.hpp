#ifndef _Player_hpp
#define _Player_hpp

/** A player is identified by his/her probability of winning a point
 * when he/she serves that point. 
 */

class Score;

class Player {

public: 
    Player( int prob );
    void setProbabilityOfWinningAServe( int prob );
    int getProbabilityOfWinningAServe();
    Score *serveAPoint();
    static Player *otherPlayer( Player *p )    {
	    return players[ (p->myPlayerIdx + 1) % 2 ];
    }

private: 
    int probOfWinningAServe;
    int myPlayerIdx;
    static Player *players[2];
    static int playersIdx;
    int getARandomNumber( int low, int high );

};

#endif
