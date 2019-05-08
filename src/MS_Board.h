/*
 * MS_Board.h
 *
 *  Created on: May 7, 2019
 *      Author: Connor
 */

#include <vector>
#include <iostream>
#include <ctime>
#include <unordered_set>
#include <utility>
#include <queue>

#ifndef MS_BOARD_H_
#define MS_BOARD_H_

class MS_Board{
public:
	MS_Board();
	void playGame();
private:
	std::vector<std::vector<int> > playSpace;
	std::vector<std::vector<bool> > flagged;
	void displayBoard();
	int flaggedMines;
	int numFlags;
	void setValues();
	void placeMines();
	std::vector<std::pair<int, int> > getNeighbors(int row, int col);
	int openSpot(int row, int col);
	void flagSpot(int row, int col);
	void processNeighbors(int row, int col, int flag);
	bool sanitaryInput(int row, int col, char operation, int& count);
	bool oob(int row, int col);
};



#endif /* MS_BOARD_H_ */
