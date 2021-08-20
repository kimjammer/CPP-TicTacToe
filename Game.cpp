//
// Created by John Kim on 8/19/2021.
//

#include <iostream>
#include <string>
#include "Game.h"

using namespace std;

/*Constructor*/
Game::Game(int boardSize /*= 3*/) {
	m_boardSize = boardSize;

	vector<int> boardRow(m_boardSize);
	vector<vector<int> > boardFull(m_boardSize, boardRow);
	m_gameBoard = boardFull;
}

/*Game Class methods*/
vector<vector<int> > Game::getBoard() const {
	return m_gameBoard;
}

int Game::getSize() const {
	return m_boardSize;
}

void Game::makeMove(int playerId, int row, int column) {
	m_gameBoard[row][column] = playerId;
}

void Game::printBoard() const {
	string output = "";

	for (int i = 0; i < m_boardSize; i++) {

		for (int j = 0; j < m_boardSize; j++) {
			switch (m_gameBoard[i][j]) {
				case 0:
					output += " ";
					break;
				case 1:
					output += "O";
					break;
				case 2:
					output += "X";
					break;
			}

			//Output vertical line to divide columns
			if (j < m_boardSize - 1) output += "|";
		}
		output += '\n';
	}

	cout << output;
}

/*
Check if the game is full
*/
bool Game::isFull() const {
	for (vector<int> row : m_gameBoard) {
		for (int spot : row) {
			if (spot == 0) return false;
		}
	}

	return true;
}

/*
Checks if the current game is over.
Returns 1 if player 1 won
Return 2 if player 2 won
Returns 0 if noone has won and game is ongoing
Returns -1 if it is a tie.
*/
int Game::gameOverCheck() const {
	bool rowExists = true;

	//Check all rows
	int firstMarkerPlayer;
	for (vector<int> row : m_gameBoard) {
		firstMarkerPlayer = row[0];
		rowExists = true;

		//Check the markers in the row
		for (int spotPlayer : row) {
			if (spotPlayer != firstMarkerPlayer) {
				//If current marker is different from the first marker, can't be all-in-a-row, so break & check next row.
				rowExists = false;
				break;
			}
		}

		if (rowExists) {
			return firstMarkerPlayer;
		}
	}

	//Check all columns
	for (int columnNum = 0; columnNum < m_boardSize; columnNum++) {
		firstMarkerPlayer = m_gameBoard[0][columnNum];
		rowExists = true;

		//Check the markers in the column
		for (int rowNum = 0; rowNum < m_boardSize; rowNum++) {
			if (m_gameBoard[rowNum][columnNum] != firstMarkerPlayer) {
				//If current marker is different from the first marker, can't be all-in-a-row, so break & check next column.
				rowExists = false;
				break;
			}
		}

		if (rowExists) {
			return firstMarkerPlayer;
		}
	}

	//Check diagonal top-left to bottom-right
	int columnNum = 0;
	int rowNum = 0;
	firstMarkerPlayer = m_gameBoard[rowNum][columnNum];
	rowExists = true;

	//Check the markers in the diagonal
	for (int rowNum = 0; rowNum < m_boardSize; rowNum++, columnNum++) {
		if (m_gameBoard[rowNum][columnNum] != firstMarkerPlayer) {
			//If current marker is different from the first marker, can't be all-in-a-row, so break.
			rowExists = false;
			break;
		}
	}

	if (rowExists) {
		return firstMarkerPlayer;
	}

	//Check diagonal top-right to bottom-left
	columnNum = m_boardSize - 1;
	rowNum = 0;
	firstMarkerPlayer = m_gameBoard[rowNum][columnNum];
	rowExists = true;

	//Check the markers in the diagonal
	for (int rowNum = 0; rowNum < m_boardSize; rowNum++, columnNum--) {
		if (m_gameBoard[rowNum][columnNum] != firstMarkerPlayer) {
			//If current marker is different from the first marker, can't be all-in-a-row, so break.
			rowExists = false;
			break;
		}
	}

	if (rowExists) {
		return firstMarkerPlayer;
	}

	//Check if board is full (and no winner so far)
	//This checks for a tie
	if (this->isFull()) {
		return -1;
	}

	//If no winner, return 0
	return 0;
}