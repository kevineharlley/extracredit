#pragma once
//TicTacToe.h


#include "stdafx.h"
#include "GameBase.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include<sstream>
#include <locale>

using namespace std;

#ifndef TICTACTOE_H
#define TICTACTOE_H
#endif // !TICTACTOE_H


class Tictactoegame : public GameBase
{
public:
	Tictactoegame();
	Tictactoegame(int wSize, int tSize);
	int play();
	void save();
	void setTurn();
	int prompt(unsigned int& i, unsigned int & k);
	virtual	bool done();
	virtual bool draw();
	virtual bool turn();
	virtual void print();
	friend ostream &operator<<(ostream &out, const Tictactoegame & gpVariable); //access to private me

};



