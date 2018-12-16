#pragma once

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include<sstream>
#include <locale>
#include <iomanip>
#define tictactoewidth 3
#define gomokuwidtharg 2
#define gomokurowsarg 3
#include <memory>
#include "GamePiece.h"

#ifndef GAMEBASE_H
#define GAMEBASE_H
#endif // !GAMEBASE_H



using namespace std;

enum commandArgument { programname, filename };

enum returnValue2 { Success, fileNotOpen, numOfArguments, failure2, couldNotRead2, extractError, wrongArguments, exceptions }; //enum easy for user to read

enum prompt { validPair, quit, invalidPair, validLength };
enum Turn { trueTurn, exitGame, failure, endGame, spotTaken };
enum play { successPlay, failurePlay };
class GameBase {
public:
	//define each function 

	GameBase();
	GameBase(int wSize, int tSize);
	virtual bool done() = 0;
	virtual bool draw() = 0;
	virtual bool turn() = 0;
	virtual int play() = 0;
	virtual int prompt(unsigned int& i, unsigned int &k);
	static shared_ptr<GameBase> basePointer;
	

	virtual void print() = 0;
	shared_ptr<GameBase> instance();
	friend ostream &operator <<(ostream &out, const GameBase& gpVariable); //access to private me
	static void checkargs(int argc, char* argv[]);

protected:

	int wide;
	int tall;
	int counterX;
	int counterO;
	GamePiece** squares; //2D dynamic array 
	vector<string>coordinatesX; //storing coordinates Player A
	vector<string>coordinatesO; //storing coordinates Player B
	bool whoseTurn = true;
	int maxString = 1;
};

