#include "tictactoe.h"
#include <iostream>
#include <vector>

int main()
{
	Board board{};
	std::vector<int> moves{ board.possible_moves() };
	for(int i : moves)
	{
		std::cout << i << ' ';
	}
	std::cout << '\n';
	board.place( moves.at(0), false);
	board.place( moves.at(1), false);
	board.place( moves.at(2), false);
	moves = board.possible_moves();
	for(int i : moves)
	{
		std::cout << i << ' ';
	}
	std::cout << '\n';
}
