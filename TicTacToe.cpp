#include "TicTacToe.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

TicTacToe::TicTacToe() {
	pp_cGrid = new char* [3];
	pp_cGrid[0] = new char[3];
	pp_cGrid[1] = new char[3];
	pp_cGrid[2] = new char[3];
}

TicTacToe::~TicTacToe() {
	cout << "Destroying your glorious dynamically allocated Grid" << endl;
	delete[] pp_cGrid[0];
	delete[] pp_cGrid[1];
	delete[] pp_cGrid[2];
	delete[] pp_cGrid;
}

void TicTacToe::Play() {
	//Variables
	int CatsGame = 0;
	string playString = "n";
	bool isPlaying = false;
	//Start
	PopulateGrid();
	int down;
	int right;
	char inputChar;
	cout << "<><><>Welcome to TicTacToe<><><>" << endl;
	cout << "\n" << "Press P to play, or I for more information." << endl;
	cin >> playString;
	if (playString == "i" || "I" == playString) {
		isPlaying = true;
		cout << "The game works using a 3 x 3 grid, each with a character inside. " << "\n" <<
			"It starts out empty, and as you place your X's the computer will place its O's." << "\n" <<
			"Place your peices by entering their coordinates from (0,0) to (2,2)" << endl;
	}
	else if (playString == "P" || playString == "p") {
		isPlaying = true;
	}
	while (isPlaying) {
		if (CatsGame >= 9) {
			string inputCat;
			PrintGrid();
			cout << "Cats Game" << "\n" << "Would you like to play again? (y for yes anything for no)" << endl;
			cin >> inputCat;
			if (inputCat == "y") {
				cout << "New Game" << endl;
				CatsGame = 0;
				PopulateGrid();
				continue;
			}
			isPlaying = false;
			continue;
		}
		PrintGrid();
		cout << "Please enter the first coordinate (0-2)" << endl;
		down = getNextInput();
		while (down > 2 || down < 0) {
			cout << "Wrong input, Please use the correct range (0-2)" << endl;
			down = getNextInput();
		}
		cout << "Please enter the second coordinate (0-2)" << endl;
		right = getNextInput();
		while (right > 2 || right < 0) {
			cout << "Wrong input, Please use the correct range (0-2)" << endl;
			right = getNextInput();
		}

		if (TryTurn(down, right)) {
			CatsGame++;
			pp_cGrid[down][right] = 'X';
		}
		else {
			cout << "Please try again" << endl;
			continue;
		}

		if (CheckForWinner() == 'X') {
			string input;
			PrintGrid();
			cout << "Congradulations you won!" << "\n" << "Would you like to play again? (y for yes anything for no)" << endl;
			cin >> input;
			if (input == "y") {
				cout << "New Game" << endl;
				CatsGame = 0;
				PopulateGrid();
				continue;
			}
			isPlaying = false;
			continue;
		}
		PlayAdvancedComputer();
		CatsGame++;
		PrintGrid();
		cout << endl;
		if (CheckForWinner() == 'O') {
			string inputLoss;
			PrintGrid();
			cout << "You lost." << "\n" << "Would you like to play again? (y for yes anything for no)" << endl;
			cin >> inputLoss;
			if (inputLoss == "y") {
				CatsGame = 0;
				cout << "New Game" << endl;
				PopulateGrid();
				continue;
			}
			isPlaying = false;
			continue;
		}
	}

	cout << "Thanks for Playing" << endl;
	
	//this->PrintGrid();
}

void TicTacToe::PopulateGrid() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			pp_cGrid[i][j] = '~';
		}
	}
}

void TicTacToe::PrintGrid() {
	for (int i = 0; i < 3; i++) {
		if (i == 1 || i == 2) {
			cout << endl;
		}
		for (int j = 0; j < 3; j++) {
			cout << pp_cGrid[i][j];
		}
	}
	cout << endl;
}


void TicTacToe::PlayForComputer() {//original algorithm
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (pp_cGrid[i][j] == '~') {
				pp_cGrid[i][j] = 'O';
				return;
			}
		}
	}
}

void TicTacToe::PlayAdvancedComputer() {
	int randDown = rand() % 2 + 0;
	int randRight = rand() % 2 + 0;
	if (pp_cGrid[randDown][randRight] == '~') {
		pp_cGrid[randDown][randRight] = 'O';
	}
	else {
		PlayForComputer();
		cout << "Can't make smart decision, using archaic move determiniation for this turn." << endl;
	}
}


int TicTacToe::getNextInput() {
	int c;
	cin >> c;
	return c;
}

bool TicTacToe::TryTurn(int down, int right) {
	if (pp_cGrid[down][right] == '~') {
		return true;
	}
	else {
		return false;
	}
}

char TicTacToe::CheckForWinner() {
	//top 3 row
	if (pp_cGrid[0][0] == pp_cGrid[0][1] && pp_cGrid[0][1] == pp_cGrid[0][2]) {
		return pp_cGrid[0][0];
	}
	//middle 3 row
	else if (pp_cGrid[1][0] == pp_cGrid[1][1] && pp_cGrid[1][1] == pp_cGrid[1][2]) {
		return pp_cGrid[1][0];
	}
	//bottom 3 row
	else if (pp_cGrid[2][0] == pp_cGrid[2][1] && pp_cGrid[2][1] == pp_cGrid[2][2]) {
		return pp_cGrid[2][0];
	}
	//first 3 collumn
	else if (pp_cGrid[0][0] == pp_cGrid[1][0] && pp_cGrid[1][0] == pp_cGrid[2][0]) {
		return pp_cGrid[0][0];
	}
	//middle 3 collumn
	else if (pp_cGrid[0][1] == pp_cGrid[1][1] && pp_cGrid[1][1] == pp_cGrid[2][1]) {
		return pp_cGrid[0][1];
	}
	//right 3 collumn
	else if (pp_cGrid[0][2] == pp_cGrid[1][2] && pp_cGrid[1][2] == pp_cGrid[2][2]) {
		return pp_cGrid[0][2];
	}
	//top left diag
	else if (pp_cGrid[0][0] == pp_cGrid[1][1] && pp_cGrid[1][1] == pp_cGrid[2][2]) {
		return pp_cGrid[0][0];
	}
	//top right diag
	else if (pp_cGrid[0][2] == pp_cGrid[1][1] && pp_cGrid[1][1] == pp_cGrid[2][0]) {
		return pp_cGrid[0][2];
	}
	else {
		return 'q';
	}
}