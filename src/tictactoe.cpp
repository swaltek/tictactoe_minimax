#include "tictactoe.h"
#include <bitset>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

BoardValue Board::at(int index) const{
	if(index < 0 || 8 < index) throw std::out_of_range{ "Index out of Board range" };
	if(filled_bits().test(index) == true)
	{
		return (o_bits.test(index) ? BoardValue::o : BoardValue::x);
	}
	else return BoardValue::none;
}

bool Board::check_tie() const
{
	std::bitset<9> full_board{ "111111111" };
	if( full_board == (filled_bits() & full_board) ) return true;
	return false;
}

bool Board::check_win(bool o) const
{
	const std::bitset<9>& bits = o ? o_bits : x_bits; //bits to be checked

	//diagonals
	if(bits.test(4) != false) //if middle is not taken no diagonals will pass
	{
		std::bitset<9> forward_diagonal{ "100010001" }; //bits of '\'
		std::bitset<9> backward_diagonal{ "001010100" }; //bits of '/'
		if(forward_diagonal == (bits & forward_diagonal)) return true;
		if(backward_diagonal == (bits & backward_diagonal)) return true;
	}

	//columns and rows
	std::bitset<9> col_check{ "001001001" }; //bits of the first column/row
	std::bitset<9> row_check{ "000000111" };
	for(int i = 0; i < 3; ++i) // loop for all 3 columns and rows
	{
		if(col_check == (bits & col_check)) return true;
		if(row_check == (bits & row_check)) return true;
		col_check = col_check << 1; //move over a column/row over
		row_check = row_check << 3;
	}

	return false;
}

//returns false if index is occupied
bool Board::place(int index, bool o)
{
	if(at(index) != BoardValue::none) return false;

	std::bitset<9>& bits = o ? o_bits : x_bits; //bits to be changed
	bits.set(index);
	return true;
}

//returns indexes of free spaces
//all returned indexes will return true when used in place(int,bool)
std::vector<int> Board::possible_moves() const
{
	const std::bitset<9> bits = filled_bits();
	std::vector<int> moves{};
	//loop through each bit and add the index of the ones that are 0 to possible_moves
	for(int i = 0; i < 9; ++i)
	{
		if( bits.test(i) == false)
		{
			moves.push_back(i);
		}#include <utility>
	}
	return moves;
}

int AI::best_move(const Board& board)
{
	minimax(board, 0, true);
	return choice;
}

int AI::minimax(const Board& position, int depth, bool maxPlayer)
{
	//check position game state and return score if game is lost, won, or tied
	if(position.check_win(!is_o)) //AI loses
	{
		return depth - 10;
	}
	else if(position.check_win(is_o)) //AI wins
	{
		return 10 - depth;
	}
	else if(position.check_tie())
	{
		return 0;
	}

	//do minimax calculation
	if(maxPlayer)
	{
		int max_move{};
		int max_move_score{ std::numeric_limits<int>::min()};
		for(int move : position.possible_moves())
		{
			Board possible_position{ position };
			possible_position.place(move, is_o);
			int score = minimax(possible_position, ++depth, false);
			if ( score > max_move_score )
			{
				max_move = move;
				max_move_score = score;
			}
		}

		choice = max_move;//last call to this will be at first call to minimax() from best_move()
		return max_move_score; //return max score
	}
	else
	{
		int min_move{};
		int min_move_score{ std::numeric_limits<int>::max()};
		for(int move : position.possible_moves())
		{
			Board possible_position{ position };
			possible_position.place(move, !is_o);
			int score = minimax(possible_position, ++depth, true);
			if ( score < min_move_score )
			{
				min_move = move;
				min_move_score = score;
			}
		}

		return min_move_score; //return max score
	}
}
