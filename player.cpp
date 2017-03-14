// I made a change - David
// Me too! - Sasha
// Another try

#include "player.hpp"

/* Map of the values of each square used in getResultScore
 *      _________________________________
 *      |100| 10| 60| 60| 60| 60| 10|100|
 *      |___|___|___|___|___|___|___|___|
 *      | 10| 1 | 30| 30| 30| 30| 1 | 10|
 *      |___|___|___|___|___|___|___|___|
 *      | 60| 30| 50| 40| 40| 50| 30| 60|
 *      |___|___|___|___|___|___|___|___|
 *      | 60| 30| 40| 40| 40| 40| 30| 60|
 *      |___|___|___|___|___|___|___|___|
 *      | 60| 30| 40| 40| 40| 40| 30| 60|
 *      |___|___|___|___|___|___|___|___|
 *      | 60| 30| 50| 40| 40| 50| 30| 60|
 *      |___|___|___|___|___|___|___|___|
 *      | 10| 1 | 30| 30| 30| 30| 1 | 10|
 *      |___|___|___|___|___|___|___|___|
 *      |100| 10| 60| 60| 60| 60| 10|100|
 *      |___|___|___|___|___|___|___|___|
 */
int valueMap[64] = {20, 2, 10, 10, 10, 10, 2, 20,
                    2, 0, 4, 4, 4, 4, 0, 2,
                    10, 4, 6, 5, 5, 6, 4, 10,
                    10, 4, 5, 5, 5, 5, 4, 10,
                    10, 4, 5, 5, 5, 5, 4, 10,
                    10, 4, 6, 5, 5, 6, 4, 10,
                    2, 0, 4, 4, 4, 4, 0, 2,
                    20, 2, 10, 10, 10, 10, 2, 20,};

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) 
{
    testingMinimax = false;
    this->side = side;
    board = new Board();
}

/*
 * Destructor for the player.
 */
Player::~Player() 
{
	delete board;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft)
{
    board->doMove(opponentsMove, (side == BLACK) ? WHITE : BLACK);
    Move *bestMove = nullptr;

    // Normal method
    if (!testingMinimax)
    {

     // Original, heuristic only no minimax

     //    int maxScore = -1;
     //    if (board->hasMoves(side))
    	// {
    	// 	for (int i = 0; i < 8; i ++)
    	// 	{
    	// 		for (int j = 0; j < 8; j ++)
    	// 		{
     //                Move *move = new Move(i, j);
    	// 			if (board->checkMove(move, side))
    	// 			{
     //                    int resultScore = getResultScore(board, move, side);
     //                    if (resultScore > maxScore)
     //                    {
     //                        bestMove = move;
     //                        maxScore = resultScore;
     //                    }
     //                }	
    	// 		}
    	// 	}
    	// }

     // 4 deep minimax using heuristic defined in getResultScore

        int maxMinScore = -1;
        for (int a = 0; a < 8; a ++)
        {
            for (int b = 0; b < 8; b ++)
            {
                Move *move1 = new Move(a, b);
                if (board->checkMove(move1, side))
                {
                    Board *newBoard1 = board->copy();
                    newBoard1->doMove(move1, side);
                    int minScore = 6401;
                    for (int c = 0; c < 8; c ++)
                    {
                        for (int d = 0; d < 8; d ++)
                        {
                            Move *move2 = new Move(c, d);
                            if (newBoard1->checkMove(move2, (side == BLACK) ? WHITE : BLACK))
                            {
                                Board *newBoard2 = newBoard1->copy();
                                newBoard2->doMove(move2, (side == BLACK) ? WHITE : BLACK);
                                for (int e = 0; e < 8; e ++)
                                {
                                    for (int f = 0; f < 8; f ++)
                                    {
                                        Move *move3 = new Move(e, f);
                                        if (newBoard2->checkMove(move3, side))
                                        {
                                            Board *newBoard3 = newBoard2->copy();
                                            newBoard3->doMove(move3, side);
                                            for (int g = 0; g < 8; g ++)
                                            {
                                                for (int h = 0; h < 8; h ++)
                                                {
                                                    Move *move4 = new Move(g, h);
                                                    if (newBoard3->checkMove(move4, (side == BLACK) ? WHITE : BLACK))
                                                    {
                                                        int score = getResultScore(newBoard3, move4, (side == BLACK) ? WHITE : BLACK);
                                                        if (score < minScore)
                                                        {
                                                            minScore = score;
                                                        }
                                                    }
                                                }
                                            }
                                            delete newBoard3;
                                        }
                                    }
                                }
                                delete newBoard2;
                            }
                        }
                    }
                    if (minScore > maxMinScore)
                    {
                        maxMinScore = minScore;
                        bestMove = move1;
                    }
                    delete newBoard1;
                }
            }
        }
    }


    // Only used when calling testminimax
    else
    {
        int maxMinScore = -65;
        for (int i = 0; i < 8; i ++)
        {
            for (int j = 0; j < 8; j ++)
            {
                Move *move1 = new Move(i, j);
                if (board->checkMove(move1, side))
                {
                    Board *newBoard1 = board->copy();
                    newBoard1->doMove(move1, side);
                    int minScore = 65;
                    for (int k = 0; k < 8; k ++)
                    {
                        for (int l = 0; l < 8; l ++)
                        {
                            Move *move2 = new Move(k, l);
                            if (newBoard1->checkMove(move2, (side == BLACK) ? WHITE : BLACK))
                            {
                                Board *newBoard2 = newBoard1->copy();
                                newBoard2->doMove(move2, (side == BLACK) ? WHITE : BLACK);
                                int score = newBoard2->count(side) - newBoard2->count((side == BLACK) ? WHITE : BLACK);
                                if (score < minScore)
                                {
                                    minScore = score;
                                }
                                delete newBoard2;
                            }
                        }
                    }
                    if (minScore > maxMinScore)
                    {
                        maxMinScore = minScore;
                        bestMove = move1;
                    }
                    delete newBoard1;
                }
            }
        }
    }

    board->doMove(bestMove, side);
    return bestMove;
}

/*
 * Given a possible move that the player could make and the current player making 
 * a move, returns the score for our player after the move has been made. 
 * 
 * score = valueMap[move x][move y] * number of spaces owned 
 */
int Player::getResultScore(Board *b, Move *move, Side s)
{
    Board *newBoard = b->copy();
    newBoard->doMove(move, s);
    int before = b->count(side) - b->count((side == BLACK) ? WHITE : BLACK);
    int after = newBoard->count(side) - newBoard->count(((side == BLACK) ? WHITE : BLACK));
    int score = (after - before);
    score *= valueMap[(move->getX() + 1) * (move->getY() + 1) - 1];
    delete newBoard;
    return score;
}
