/*
 * MS_Board.cpp
 *
 *  Created on: May 7, 2019
 *      Author: Connor
 */

#include "MS_Board.h"

MS_Board::MS_Board(){ //create board an initialize values to zero
	std::vector<int> temp;
	for(int i = 0; i < 10; ++i){
		temp.push_back(10);
	}
	for(int i = 0; i < 10; ++i){
		playSpace.push_back(temp);
	}
	placeMines();
	setValues(); //set values to represent number of adjacent mines
}

void MS_Board::placeMines(){
	srand(time(0));
	std::unordered_set<int> minePos;
	int i = 0;
	while(i < 10){ //generate 10 random numbers between 1 and 100 representing mine positions
		int random = rand() % 100;
		if(minePos.find(random) == minePos.end()){
			minePos.insert(random);
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
			if(playSpace[row][col] >= 9){
				std::cout << "/ ";
			}
			else{
				std::cout << playSpace[row][col] << " ";
			}
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

int MS_Board::pickSpot(int row, int col){
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
				if(!oob(first, second) && playSpace[first][second] == 10){
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

void MS_Board::playGame(int row, int col){//TODO
	int gameStatus = pickSpot(row, col);
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

bool MS_Board::oob(int row, int col){//check out of bounds
	if(row < 0 || col < 0 || row > 9 || col > 9){
		return true;
	}
	else{
		return false;
	}
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


