#ifndef TICTACTOE_H
#define TICTACTOE_H

class TicTacToe {
public:
	TicTacToe();
	~TicTacToe();
	
	void Play();
	void PopulateGrid();
	void PrintGrid();
	
	void PlayForComputer();
	void PlayAdvancedComputer();
	
	int getNextInput();
	bool TryTurn(int down, int right);
	char CheckForWinner();

private:
	char** pp_cGrid;
};



#endif