/*
   The program simulates a tennis match.  It first draws a random
   number to decide which of the two players serves the first game of
   the match.  Given the probability of player A winning a point
   against player B if she is serving, the function `point' decides
   the outcome of the point.  To make the program more realistic, one
   needs to change the way the function `point' decides which player
   wins a point.

   The rules of the game are: 

   A match is won by the first player to win 3 sets.  A set is won by
   the first player to win 6 games if ahead by two games. If the set
   reaches a score of 6-5, another game is played.  If the player who
   is ahead wins that game, the set is over, won by a score of 7-5.
   Otherwise the score is 6-6 and a tie breaker is played. The winner
   of the tie breaker is the winner of the set 7-6.

   Players alternate who serves a game. The server is the player who
   first hits the ball. Player also alternate who serves the first
   game of a set.  A game is won by the first player to get at
   least 4 points and be ahead by two points. Tennis uses a strange
   way of counting points.  We can simply count points by 0,1,2,...

   Points are the basic unit of play.  A point consists of a player
   putting the ball into play (serving) followed by the two players
   hitting it back and forth until something goes wrong such as the
   ball is hit out of bounds.

   A tie breaker is a game in which the first player to score at least
   seven and be ahead by two wins.  The service in a tie breaker
   alternates. The player whose turn it would be to serve in a normal
   game serves once. Thereafter the players alternate serving twice
   until the tie breaker is over.

   Written by: Ali A. Kooshesh

*/

#include<iostream>
#include<iomanip>
#include<stdlib.h>

using namespace std;

enum players {PLAYER1, PLAYER2};
inline players other(int player) 
{ 
     return player == PLAYER1 ? PLAYER2 : PLAYER1;
}

/*               FUNCTION PROTOTYPES                            */

players point( players );
players game( players  );
players tie_breaker( players , int &, int & );
players set( players , int );
players match( players , int &, int & );
   
/*     END OF FUNCTION PROTOTYPES                              */

int p;   // probablility of player A winning the point that he/she serves.
int q;   // probablility of player B winning the point that he/she serves.

inline int random( int upper_bound )
{
     return rand() % upper_bound + 1;
}

players point( players player )
/* Player 'player' serves a point and the outcome is returned.  */
{
     int prob = player == PLAYER1 ? p : q;
     return random(100) <= prob ? player : other(player);
}

inline int game_over(int a, int b) 
{ 
     return ( a >= 4 || b >= 4 ) && abs(a - b) >= 2;
}

players game( players player )
/* Player `player' serves a new game and the outcome is returned. */
{
     int p1_npts = 0, p2_npts = 0;
     
     while( ! game_over( p1_npts, p2_npts ) ) 
	  point( player ) == PLAYER1 ? p1_npts++ : p2_npts++;
     return p1_npts > p2_npts ? PLAYER1 : PLAYER2;
}


inline int tie_over(int a, int b) 
{
     return (a >= 7 || b >= 7) && abs(a - b) >= 2;
}

players tie_breaker( players player, int &p1_score, int &p2_score )
/* A tie-breaker game is played by player 'player' serving first.
   The function returns the winner of the game.  Also, the score for
   each player (number of points won) is stored in `p1_score' and
   `p2_score'.
*/  
{
     p1_score = p2_score = 0;
     point( player ) == PLAYER1 ? p1_score++ : p2_score++;
     int switchServe = 0;
     do {
	  if( switchServe++ % 2 == 0 ) player = other(player);
	  point( player ) == PLAYER1 ? p1_score++ : p2_score++;
     } while ( ! tie_over( p1_score, p2_score ) );
     return p1_score > p2_score ? PLAYER1 : PLAYER2;
}


inline int Awin(int a, int b) {return (a >= 6 || b >= 6) && abs(a - b) >= 2;}
inline int areTied(int a, int b) { return a == 6 && b == 6; }
inline int set_over(int a, int b) { return (Awin(a, b)) || (areTied(a, b)); }
players set( players player, int set_number )
/* A set is played by player 'player' serving first and the result is
   reported (printed out.)  The function returns the winner of the
   set.  If a tie-breaker is played, the score for that game is also
   printed.
*/
{
     int p1_gscore = 0, p2_gscore = 0;
     do {
	  game( player ) == PLAYER1 ? p1_gscore++ : p2_gscore++;
	  player = other(player);
     } while( ! set_over( p1_gscore, p2_gscore ) );
     int p1_tscore = 0, p2_tscore = 0;
     if( areTied( p1_gscore, p2_gscore ) )
	  tie_breaker( player, p1_tscore, p2_tscore ) == PLAYER1 ? 
	       p1_gscore++ : p2_gscore++;
     cout << setw(7) << set_number << setw(10) << p1_gscore << setw(18) << p2_gscore;
     if( p1_tscore != 0 || p2_tscore != 0 )
	       cout << setw(16) << "(tie breaker  " << p1_tscore << "-" <<
	       p2_tscore << ")";
     cout << endl;
     return p1_gscore > p2_gscore ? PLAYER1 : PLAYER2;
}

inline int match_over(int a, int b) { return a == 3 || b == 3; }
players match( players player, int &p1_sscore, int &p2_sscore )
/* A match is played by player 'player' serving first.  The function
   returns the winner of the match.  Also, it stores the number of
   sets that each player has won in p1_sscore and p2_sscore.
*/   
{
     p1_sscore = p2_sscore = 0;
     int set_number = 0;
     do {
	  set_number++;
	  set(player, set_number) == PLAYER1 ? p1_sscore++ : p2_sscore++;
	  player = other(player);
     } while( ! match_over( p1_sscore, p2_sscore ) );
     return p1_sscore > p2_sscore ? PLAYER1 : PLAYER2;
}

int main( void )
{
     int p1_sscore, p2_sscore;

     int seed;
     cout << "Enter the seed value for the random number generator? ";
     cin >> seed;
     srand( seed );

     players player = PLAYER1;

     cout << "Please enter the probablility of player A winning when (s)he serves: "; 
     cin >> p;
     cout << "Please enter the probablility of player B winning when (s)he serves: "; 
     cin >> q;
     cout << "   Set No.    Player A          Player B\n";  
     player = match( player, p1_sscore, p2_sscore );
     if( p1_sscore > p2_sscore )
	  cout << "\nPlayer A wins the match " << p1_sscore << " sets to "
	       << p2_sscore << endl;
     else
	  cout << "\nPlayer B wins the match " << p2_sscore << " sets to "
	       << p1_sscore << endl;

     return 0;
}
