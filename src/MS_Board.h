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
	void displayBoard();
	void playGame(int row, int col); //TODO
private:
	std::vector<std::vector<int> > playSpace;
	void setValues();
	void placeMines();
	std::vector<std::pair<int, int> > getNeighbors(int row, int col);
	int pickSpot(int row, int col);
	void processNeighbors(int row, int col, int flag);
	bool oob(int row, int col);
};



#endif /* MS_BOARD_H_ */
