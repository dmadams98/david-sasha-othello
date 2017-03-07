#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    int getResultScore(Move *move);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    // Side the player is on (WHITE or BLACK)
    Side side;
    // Board used to keep track of the moves made
    Board *board;
    // Number of tyles owned by player - number of tiles owned by opponent
    int score;
    /* Map of the values of each square
	 *      _________________________________
	 *		| 5 | -2| 3 | 3 | 3 | 3 | -2| 5 |
	 *		|___|___|___|___|___|___|___|___|
	 *      | -2| -2| -1| -1| -1| -1| -2| -2|
	 *		|___|___|___|___|___|___|___|___|
	 *      | 3 | -1| 2 | 1 | 1 | 2 | -1| 3 |
	 *		|___|___|___|___|___|___|___|___|
	 *      | 3 | -1| 1 | 1 | 1 | 1 | -1| 3 |
	 *		|___|___|___|___|___|___|___|___|
	 *      | 3 | -1| 1 | 1 | 1 | 1 | -1| 3 |
	 *		|___|___|___|___|___|___|___|___|
	 *      | 3 | -1| 2 | 1 | 1 | 2 | -1| 3 |
	 *		|___|___|___|___|___|___|___|___|
	 *      | -2| -2| -1| -1| -1| -1| -2| -2|
	 *		|___|___|___|___|___|___|___|___|
	 *		| 5 | -2| 3 | 3 | 3 | 3 | -2| 5 |
	 *		|___|___|___|___|___|___|___|___|
	 */
};

#endif
