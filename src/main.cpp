#include "tictactoe.h"
#include <array>
#include <ctime>
#include <iostream>
#include <random>
#include <string>

int ask_player_input()
{
	bool retry{ false };
	int index{};

	std::cout << "It's your turn. Where do you want to go(e.g. A1 B3 C2)? ";
	do{
		if(retry)
		{
			std::cout << "No, no, no! Input a letter followed by a number: ";
		}
		retry = false; //reset retry

		std::string input;
		std::cin >> input;
		if(input.size() < 2)
		{
			retry = true;
			continue;
		}
	
		//letter input
		int col_input{};
		switch(input.at(0))
		{
			case 'A':
			case 'a':
				col_input = 0;
				break;
			case 'B':
			case 'b':
				col_input = 1;
				break;
			case 'C':
			case 'c':
				col_input = 2;
				break;
			default:
				retry = true;
				continue;
		}
	
		//number input
		int row_input = input.at(1) - '0'; //converts char '2' to int 2
		if(--row_input < 0 || 3 < row_input)
		{
			retry = true;
			continue;
		}
	
		index = col_input * 3 + row_input;
	} while( retry );
	return index;
}

bool ask_turn() //ask who will go first if return true O goes first
{
	bool turn{};
	std::string input;
	std::cout << "Who do you want to be?(X or O)? ";
	for(bool valid_input{false}; !valid_input;)
	{
		std::cin >> input;
		switch(input.front()) //input cannot be null at this point
		{
			case 'x':
			case 'X':
				valid_input = true;
				turn = false;
				break;
			case '0':
			case 'o':
			case 'O':
				valid_input = true;
				turn = true;
				break;
			default:
				std::cout << "Invalid input! Try X or O :";
		}
	}
	return turn;
}

std::ostream& print_board(std::ostream& os,const Board& board)
{
	os << " |A|B|C\n";
	for(int row = 0; row < 3; ++row)
	{
		os << std::string( 8, '-') << '\n';
		os << row + 1 << '|';
		for(int col = 0; col < 3; ++col)
		{
			char follow_char{ col == 2 ? '\n' : '|' };
			char place_char{};

			//determine character to print for this board place on the board
			BoardValue place_value  = board.at(col * 3 + row);
			if(place_value == BoardValue::none) place_char = ' ';
			else place_char = place_value == BoardValue::o ? 'O' : 'X';

			os << place_char << follow_char;
		}
	}
	os << '\n';
	return os;
}

std::ostream& operator<<(std::ostream& os,const Board& board)
{
	return print_board(os, board);
}

int main(){
	std::default_random_engine e{ static_cast<long unsigned int>(time(NULL)) };
	bool turn{ e() % 2 };
	bool player_turn{ ask_turn() };
	Board board{};
	AI ai{ !player_turn };
	
	//turn will be switched at start of game loop
	if(turn != player_turn)//player first see above comment
	{
		std::cout << "You go first!\n" << board;
	}
	else std::cout << "Computer gets to go first this time. Good luck!\n";
	
	while(board.check_win(turn) == false && board.check_tie() == false)
	{
		turn = !turn;
		if(turn == player_turn)
		{
			bool input_valid{false};
			while(input_valid == false)
			{
				int input;
				input = ask_player_input();
				input_valid = board.place(input, turn);
				if( input_valid == false )
					std::cout << "That place is take! Try again...\n";
			}
		}
		else //AI turn
		{
			int best_move = ai.best_move(board);
			board.place( best_move, turn);
			std::cout << board;

			//print AI turn
			std::array<char,3> col_chars = { 'A', 'B', 'C' };
			char col_input = col_chars.at( best_move % 3 );
			int row_input = ((best_move + 1) / 3) + 1;

			std::cout << "Computer picks " << col_input << row_input << '\n';
		}
	}
	std::cout << board;
	if(board.check_tie())
	{
		std::cout << "Looks like its a tie...\n";
	}
	else std::cout << (turn == player_turn ? "You won!" : "The computer wins..." )  << '\n';
}
