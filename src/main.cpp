//============================================================================
// Name        : Minesweeper.cpp
// Author      : Connor
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "MS_Board.h"

int main() {
	MS_Board board = MS_Board();
	board.displayBoard();
	board.playGame(0,0);
	board.playGame(1,0);
	board.playGame(0,9);
	board.playGame(3,4);



	return 0;
}
