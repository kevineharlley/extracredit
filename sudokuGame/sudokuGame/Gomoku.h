#include "stdafx.h"
#include "GameBase.h"

#ifndef GOMOKU_H
#define GOMOKU_H
#endif

enum index {
	indexZero = 0, indexOne = 1, indexTwo = 2
};

class GomokuGame : public GameBase
{
public:
	GomokuGame();
	void save();
	GomokuGame::GomokuGame(const GomokuGame&);
	GomokuGame(int wSize, int tSize);
	GomokuGame(int wSize, int tSize, int newRows);
	int prompt(unsigned int& i, unsigned int & k);
	int winRows;
	virtual int play();
	virtual	bool done();
	virtual bool draw();
	void setTurn();
	virtual void fillSquares();
	virtual bool turn();
	virtual void print();
	friend ostream &operator<<(ostream &out, const GomokuGame & game); //access to private me
};
