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

#ifndef MS_BOARD_H_
#define MS_BOARD_H_

class MS_Board{
public:
	MS_Board();
	void displayBoard();
private:
	std::vector<std::vector<int> > playSpace;
	void setValues();
	void placeMines();
	std::vector<std::pair<int, int> > getNeighbors(int i, int j);
	bool oob(int i, int j);
};



#endif /* MS_BOARD_H_ */
