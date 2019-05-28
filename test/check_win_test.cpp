#include "tictactoe.h"
#include <iostream>

int main(){
	Board board{};
	board.place(2, false);
	board.place(5, false);
	board.place(8, false);
	std::cout << board.check_win(false);
}
