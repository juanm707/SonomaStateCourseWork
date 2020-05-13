#include<iostream>
#include<stdlib.h>

#include "Player.hpp"
#include "PointScore.hpp"

int MAX_PLAYERS = 2;
int Player::playersIdx = 0;
Player *Player::players[2];

Player::Player( int prob ): probOfWinningAServe( prob ) 
{
    if( Player::playersIdx == 2 ) {
	std::cerr << "You have already created " << MAX_PLAYERS << 
	    " players, which is the maximum number of players that can be created." << std::endl;
	exit( 1 );
    }
    myPlayerIdx = playersIdx;
    players[playersIdx] = this;
    playersIdx++;
}

Score *Player::serveAPoint() {
    if( playersIdx != MAX_PLAYERS ) {
	std::cerr << "You need two players to play this game!" << std::endl;
	exit( 1 );
    }
    int rand = getARandomNumber(1, 100);
    Score *score = new PointScore( players[0], players[1] );
    score->addScore( rand <= getProbabilityOfWinningAServe() ? this : Player::otherPlayer( this ) );
    return score;
  }

void Player::setProbabilityOfWinningAServe( int prob ) 
{
    probOfWinningAServe = prob;
}

int Player::getProbabilityOfWinningAServe() 
{
    return probOfWinningAServe;
}

int Player::getARandomNumber( int low, int high ) {
    return rand() % (high - low + 1) + low;
}
