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
    int getResultScore(Board *b, Move *move, Side s);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    // Side the player is on (WHITE or BLACK)
    Side side;
    // Board used to keep track of the moves made
    Board *board;
};

#endif
