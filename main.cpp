#include "TicTacToe.h"
#include <iostream>


int main() {
	TicTacToe* game = new TicTacToe();
	game->Play();
	delete game;
	return 0;
}