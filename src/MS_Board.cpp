/*
 * MS_Board.cpp
 *
 *  Created on: May 7, 2019
 *      Author: Connor
 */

#include "MS_Board.h"

MS_Board::MS_Board() : flaggedMines(0), numFlags(0){ //create board an initialize values to zero
	std::vector<int> temp;
	for(int i = 0; i < 10; ++i){
		temp.push_back(10);
	}
	for(int i = 0; i < 10; ++i){
		playSpace.push_back(temp);
	}
	std::vector<bool> boolTemp;
	for(int i = 0; i < 10; ++i){
		boolTemp.push_back(false);
	}
	for(int i = 0; i < 10; ++i){
		flagged.push_back(boolTemp);
	}
	placeMines();
	setValues(); //set values to represent number of adjacent mines
}

void MS_Board::placeMines(){
	srand(time(0));
	std::unordered_set<int> minePos;
	int i = 0;
	while(i < 10){ //generate 10 random numbers between 0 and 99 representing mine positions
		int random = rand() % 100;
		if(minePos.find(random) == minePos.end()){//the chance of taking an excessively long time to
			minePos.insert(random);              //generate 10 unique numbers was deemed acceptably low
			++i;
		}
	}
	int count = 0;
	for(int row = 0; row < 10; ++row){ //place mines
		for(int col = 0; col < 10; ++col){
			if(minePos.find(count) != minePos.end()){
				playSpace[row][col] = 9;
			}
			++count;
		}
	}
}

void MS_Board::setValues(){

	for(int row = 0; row < 10; ++row){
		for(int col = 0; col < 10; ++col){
			if(playSpace[row][col] != 9){
				processNeighbors(row, col, 9);
			}
		}
	}
}

void MS_Board::displayBoard(){
	for(int row = 0; row < 10; ++row){
		for(int col = 0; col < 10; ++col){
			if(flagged[row][col]){//flagged
				std::cout << "F ";
			}
			else if(playSpace[row][col] >= 9){//mine or unopened
				std::cout << "/ ";
			}
			else{//opened
				std::cout << playSpace[row][col] << " ";
			}
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

int MS_Board::openSpot(int row, int col){
	if(flagged[row][col]){
		std::cout << "That cell is flagged and cannot be opened.\n";
		return 0;
	}
	if(playSpace[row][col] == 9){ //9 represents a mine
		std::cout << "kaboom\n";
		return -1;
	}
	else if(playSpace[row][col] > 10){//above 10 represents a space with adjacent mine(s) which is
		playSpace[row][col] -= 10;    //currently undisplayed, subrtacting 10 will display the number
		displayBoard();
		return 0;
	}
	else if(playSpace[row][col] == 10){//10 represents a space with no adjacent mines
		std::queue<std::pair<int, int> > bfsQ;
		bfsQ.push(std::make_pair(row, col));

		while(!bfsQ.empty()){//do BFS to determine all connecting squares with no adjacent mines
			std::pair<int, int> curr = bfsQ.front();
			bfsQ.pop();
			std::vector<std::pair<int, int> > neighbors = getNeighbors(curr.first, curr.second);
			for(int k = 0; k < 8; ++k){
				int first = neighbors[k].first;
				int second = neighbors[k].second;
				if(!oob(first, second) && playSpace[first][second] == 10 && !flagged[row][col]){
					playSpace[first][second] -= 10;
					bfsQ.push(std::make_pair(first, second));
					processNeighbors(first, second, 10);//display squares adjacent to squares with no
					                                    //adjacent mines
				}
			}
		}
		displayBoard();
	}
	return 0;
}

void MS_Board::flagSpot(int row, int col){
	if(flagged[row][col]){
		--numFlags;
		flagged[row][col] = false;
		if(playSpace[row][col] == 9){
			--flaggedMines;
		}
	}
	else{
		if(numFlags >= 10){
			std::cout << "10 cells are already flagged, you must remove at least one flag before adding more.\n";
			return;
		}
		++numFlags;
		flagged[row][col] = true;
		if(playSpace[row][col] == 9){
			++flaggedMines;
		}
	}
	displayBoard();
}

void MS_Board::playGame(){
	int gameStatus = 0;
	std::cout << "To play please enter 'o' to open or 'f' to flag/unflag a cell followed by two digits"
			"'row' and 'column'\nto choose the cell[row][column] where cell[1][1] represents the top left"
			"cell of the board,\nrow increases from top to bottom, and column increases from left to right.\n\n";
	int count = 0;
	while(gameStatus != -1 && flaggedMines != 10){
		char operation = 'x';
		int row = -1;
		int col = -1;
		std::cout << "Operation: ";
		std::cin >> operation;
		std::cout << "Row: ";
		std::cin >> row;
		std::cout << "Column: ";
		std::cin >> col;
		std::cout << "\n";
		--row;
		--col;
		if(sanitaryInput( row, col, operation, count)){
			if(operation == 'f'){
				flagSpot(row, col);
			}
			else if(operation == 'o'){
				gameStatus = openSpot(row, col);
			}
		}
		else if(count > 25){
			std::cout << "Too many bad inputs.今度気を付けってルール読んで下さい。";
			return;
		}
	}
	if(gameStatus == -1){
		return;
	}
	else if(flaggedMines == 10){
		std::cout << "Congratulations, you've won! 勝ちました、 おめでとうございます！";
		return;
	}
}

std::vector<std::pair<int, int> > MS_Board::getNeighbors(int row, int col){
	std::vector<std::pair<int, int> > result;
	result.push_back(std::make_pair(row + 1, col));
	result.push_back(std::make_pair(row, col + 1));
	result.push_back(std::make_pair(row - 1, col));
	result.push_back(std::make_pair(row, col - 1));
	result.push_back(std::make_pair(row + 1, col + 1));
	result.push_back(std::make_pair(row - 1, col + 1));
	result.push_back(std::make_pair(row + 1, col - 1));
	result.push_back(std::make_pair(row - 1, col - 1));

	return result;
}

void MS_Board::processNeighbors(int row, int col, int flag){ //process neighbors according to flag value
	std::vector<std::pair<int, int> > neighbors = getNeighbors(row, col);
	for(int i = 0; i < 8; ++i){
		int first = neighbors[i].first;
		int second = neighbors[i].second;
		if(!oob(first, second)){
			if(flag == 9 && playSpace[first][second] == 9){//increase value for any adjacent mines
				++playSpace[row][col];
			}
			else if(flag == 10 && playSpace[first][second] > 10){//display if adjacent to an empty square
				playSpace[first][second] -= 10;
			}
		}
	}
}

bool MS_Board::sanitaryInput(int row, int col, char operation, int& count){
	if(oob(row, col) || (operation != 'f' && operation != 'o') || count > 25){
		++count;
		std::cout << "Bad input.\n";
		return false;
	}
	else{
		return true;
	}
}

bool MS_Board::oob(int row, int col){//check out of bounds
	if(row < 0 || col < 0 || row > 9 || col > 9){
		return true;
	}
	else{
		return false;
	}
}


