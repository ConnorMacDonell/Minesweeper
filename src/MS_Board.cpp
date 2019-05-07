/*
 * MS_Board.cpp
 *
 *  Created on: May 7, 2019
 *      Author: Connor
 */

#include "MS_Board.h"

MS_Board::MS_Board(){
	std::vector<int> temp;
	for(int i = 0; i < 10; ++i){
		temp.push_back(0);
	}
	for(int i = 0; i < 10; ++i){
		playSpace.push_back(temp);
	}
	placeMines();
	setValues();
}

void MS_Board::placeMines(){
	srand(time(0));
	std::unordered_set<int> minePos;
	int i = 0;
	while(i < 10){
		int random = rand() % 100;
		if(minePos.find(random) == minePos.end()){
			minePos.insert(random);
			++i;
		}
	}
	int count = 0;
	for(int i = 0; i < 10; ++i){
		for(int j = 0; j < 10; ++j){
			if(minePos.find(count) != minePos.end()){
				playSpace[i][j] = 9;
			}
			++count;
		}
	}
}

void MS_Board::setValues(){
	std::vector<std::pair<int, int> > neighbors;

	for(int i = 0; i < 10; ++i){
		for(int j = 0; j < 10; ++j){
			if(playSpace[i][j] != 9){
				neighbors = getNeighbors(i, j);
				for(int k = 0; k < 8; ++k){
					int first = neighbors[k].first;
					int second = neighbors[k].second;
					if(!oob(first, second) && playSpace[first][second] == 9){
						++playSpace[i][j];
					}
				}
			}
		}
	}
}

void MS_Board::displayBoard(){
	for(int i = 0; i < 10; ++i){
		for(int j = 0; j < 10; ++j){
			std::cout << playSpace[i][j] << " ";
		}
		std::cout << "\n";
	}
}

std::vector<std::pair<int, int> > MS_Board::getNeighbors(int i, int j){
	std::vector<std::pair<int, int> > result;
	result.push_back(std::make_pair(i + 1, j));
	result.push_back(std::make_pair(i, j + 1));
	result.push_back(std::make_pair(i - 1, j));
	result.push_back(std::make_pair(i, j - 1));
	result.push_back(std::make_pair(i + 1, j + 1));
	result.push_back(std::make_pair(i - 1, j + 1));
	result.push_back(std::make_pair(i + 1, j - 1));
	result.push_back(std::make_pair(i - 1, j - 1));

	return result;
}

bool MS_Board::oob(int i, int j){
	if(i < 0 || j < 0 || i > 9 || j > 9){
		return true;
	}
	else{
		return false;
	}
}


