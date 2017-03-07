// I made a change - David
// Me too! - Sasha
// Another try

#include "player.hpp"
/* Map of the values of each square
 *      _________________________________
 *      | 7 | 2 | 6 | 6 | 6 | 6 | 2 | 7 |
 *      |___|___|___|___|___|___|___|___|
 *      | 2 | 1 | 3 | 3 | 3 | 3 | 1 | 2 |
 *      |___|___|___|___|___|___|___|___|
 *      | 6 | 3 | 5 | 4 | 4 | 5 | 3 | 6 |
 *      |___|___|___|___|___|___|___|___|
 *      | 6 | 3 | 4 | 4 | 4 | 4 | 3 | 6 |
 *      |___|___|___|___|___|___|___|___|
 *      | 6 | 3 | 4 | 4 | 4 | 4 | 3 | 6 |
 *      |___|___|___|___|___|___|___|___|
 *      | 6 | 3 | 5 | 4 | 4 | 5 | 3 | 6 |
 *      |___|___|___|___|___|___|___|___|
 *      | 2 | 1 | 3 | 3 | 3 | 3 | 1 | 2 |
 *      |___|___|___|___|___|___|___|___|
 *      | 7 | 2 | 6 | 6 | 6 | 6 | 2 | 7 |
 *      |___|___|___|___|___|___|___|___|
 */
int valueMap[64] = {7, 2, 6, 6, 6, 6, 2, 7,
                    2, 1, 3, 3, 3, 3, 1, 2,
                    6, 3, 5, 4, 4, 5, 3, 6,
                    6, 3, 4, 4, 4, 4, 3, 6,
                    6, 3, 4, 4, 4, 4, 3, 6,
                    6, 3, 5, 4, 4, 5, 3, 6,
                    2, 1, 3, 3, 3, 3, 1, 2,
                    7, 2, 6, 6, 6, 6, 2, 7};
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
        int maxScore = -1;
        if (board->hasMoves(side))
    	{
    		for (int i = 0; i < 8; i ++)
    		{
    			for (int j = 0; j < 8; j ++)
    			{
                    Move *move = new Move(i, j);
    				if (board->checkMove(move, side))
    				{
                        int resultScore = getResultScore(move);
                        if (resultScore > maxScore)
                        {
                            bestMove = move;
                            maxScore = resultScore;
                        }
                    }	
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
                            Move *move2 = new Move(i, j);
                            if (newBoard1->checkMove(move2, (side == BLACK) ? WHITE : BLACK))
                            {
                                Board *newBoard2 = newBoard1->copy();
                                newBoard2->doMove(move2, (side == BLACK) ? WHITE : BLACK);
                                int score = newBoard2->count(side) - newBoard2->count((side == BLACK) ? WHITE : BLACK);
                                std::cerr << score << std::endl;
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
 * Given a possible move that the player could make, returns the score after the
 * move has been made. 
 */
int Player::getResultScore(Move *move)
{
    Board *newBoard = board->copy();
    newBoard->doMove(move, side);
    int score = newBoard->count(side);
    score *= valueMap[(move->getX() + 1) * (move->getY() + 1) - 1];
    delete newBoard;
    return score;
}
