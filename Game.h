//
// Created by John Kim on 8/19/2021.
//

#pragma once

#include <vector>

//The Game class
class Game {
private:
	std::vector<std::vector<int> > m_gameBoard;
	int m_boardSize;
public:
	std::vector<std::vector<int> > getBoard() const;

	int getSize() const;

	void makeMove(int playerId, int row, int column);

	void printBoard() const;

	bool isFull() const;

	int gameOverCheck() const;

	Game(int boardSize = 3);
};