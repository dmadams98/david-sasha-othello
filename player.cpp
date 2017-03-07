// I made a change - David
// Me too! - Sasha
// Another try

#include "player.hpp"
int valueMap[64] = {8, -6, 3, 3, 3, 3, -6, 8,
                    -6, -8, -1, -1, -1, -1, -8, -6,
                    3, -1, 2, 1, 1, 2, -1, 3,
                    3, -1, 1, 1, 1, 1, -1, 3,
                    3, -1, 1, 1, 1, 1, -1, 3,
                    3, -1, 2, 1, 1, 2, -1, 3,
                    -6, -8, -1, -1, -1, -1, -8, -6,
                    8, -6, 3, 3, 3, 3, -6, 8};
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
    score = 0;

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
    int maxScore = -9;
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
    board->doMove(bestMove, side);
    score = maxScore;
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
    int score;
    score = valueMap[(move->getX() + 1) * (move->getY() + 1) - 1];
    delete newBoard;
    return score;
}
