/*
Tic Tac Toe Player
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "header.h"
#include "Game.h"

using namespace std;

int main() {
	cout << "Welcome to C++ TicTacToe\n\n";

	int size;
	do {
		cout << "How big is your board? > ";
		size = getUserNumber();
		if (size <= 0) { cout << "Invalid board size!\n"; }
	} while (size <= 0);
	cout << endl;

	Game game(size);

	bool gameOver = false;
	int winner = 0;

	do {
		for (int i = 1; i < 3; i++) {
			playerTurn(i, game);

			winner = game.gameOverCheck();
			if (winner != 0) {
				gameOver = true;
				break;
			}
		}

	} while (!gameOver);

	game.printBoard();
	cout << "Game over!\n";
	//Check if tied
	if (winner == -1) {
		cout << "Game tied. No Winners.\n";
	} else {
		cout << "Player " << winner << " won!\n";
	}

}

void playerTurn(int playerId, Game &crrGame) {
	crrGame.printBoard();
	bool spotEmpty = true;
	int row;
	int column;

	cout << "Player " << playerId << ":\n";

	//Continously try to get a valid spot from the user
	do {

		//Get valid row
		do {
			cout << "Row num: ";
			row = getUserNumber();
			if (row > crrGame.getSize() || row <= 0) {
				cout << "Invalid, try again.\n";
			}
		} while (row > crrGame.getSize() || row <= 0);

		//Get valid column
		do {
			cout << "Column num: ";
			column = getUserNumber();
			if (column > crrGame.getSize() || column <= 0) {
				cout << "Invalid, try again.\n";

			}
		} while (column > crrGame.getSize() || column <= 0);
		cout << endl;

		//Check if spot is empty
		if (crrGame.getBoard()[row - 1][column - 1] != 0) {
			spotEmpty = false;
			cout << "Spot is already occupied!\n";
		} else {
			spotEmpty = true;
		}
	} while (!spotEmpty);

	//Make move (Minus 1 to account vector start at 0)
	crrGame.makeMove(playerId, row - 1, column - 1);
}

/*
Gets a clean int input from the user.
Returns int or -1 if failed to get int.
*/
int getUserNumber() {
	string userRawInput;
	getline(cin, userRawInput);
	istringstream userStream;
	userStream.str(userRawInput);

	int userNum;
	userStream >> userNum;
	if (userStream.fail()) {
		return -1;
	}

	return userNum;
}