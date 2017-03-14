1. Particioants contribution:

Sasha Bodrova :    - created the heuristic, the value map, changed and improved it until it was the most efficient; created the score calculation formula for the value of the possible move;
				- score = ( ( ((amount of our stones after the move) - (amount of  their stones after the move)) - ((amount of our stones before the move) - (amount of  their stones before the move)) ) * (the value of the box where we make the move) ); 
			        - wrote this README file;
				- created the condition: if there is a move that results in opponent not being able to make the move, make it;

David Adams : 	- set up the git repository 
				- wrote the code for assignment 9 - 10
				- created 4-depth minmax algorithm
 				- wrote multitest.cpp, which runs the game 10 times in a row;
				- implemented the passing condition
                               

2. Improvements:

- Better score calculation formula (heuristic);
- Better value map;
- If there is a move that results in opponent not being able to make the move, make it;
- Beats BetterPlayer, improved against SimplePlayer and ConstantPlayer

3. Improvements that we tied and they did not work:
- 4-depth minmax algorithm (somehow it makes the results much worse than just using heuristic);
- If our opponent puts a stone on the edge line (good position for him), we increase the value of boxes one  empty box from the opponent's last move (on the same edge), so that those boxes would be preferable; It was just an observation we made, we did not implement it.
