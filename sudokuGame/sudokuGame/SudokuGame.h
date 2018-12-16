#include "GameBase.h"

#ifndef GOMOKU_H
#define GOMOKU_H

#endif


class SudokuGame : public GameBase
{
public:
	SudokuGame();
	int prompt(unsigned int&, unsigned int &, string &);
	bool done();
	void setupSquares();
	int play();
	bool turn();
	bool draw();
	void save();
	void print();
	bool isValidPiece(string, int, int);
	friend ostream &operator<<(ostream &out, const SudokuGame & game); //access to private me
	int initialNumbers;
};
