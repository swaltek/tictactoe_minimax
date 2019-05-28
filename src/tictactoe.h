#ifndef TICTACTOE
#define TICTACTOE
#include <bitset>
#include <iostream>
#include <vector>

enum class BoardValue{ none, o, x};

class Board
{
public:
	Board() = default;
	Board(const Board& board): o_bits(board.o_bits), x_bits(board.x_bits) {};
	BoardValue at(int index) const;
	bool check_tie() const;
	bool check_win(bool) const;
	bool place(int, bool);
	std::vector<int> possible_moves() const;
private:
	std::bitset<9> o_bits{};
	std::bitset<9> x_bits{};
	std::bitset<9> filled_bits() const{ return o_bits | x_bits; }
};

class AI
{
public:
	AI(bool o) : is_o(o) {};
	int best_move(const Board&);
private:
	int minimax(const Board&, int, bool);

	int choice{};
	bool is_o; //is the ai playing as 'O'
};
#endif
