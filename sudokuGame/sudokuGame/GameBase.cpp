
#include "stdafx.h"
#include "GameBase.h"
#include "TicTacToe.h"
#include "Gomoku.h"
#include "sudokuGame.h"
#include <iostream>
#define SIZEARG = 2;
#define WINROWARG = 3;

using namespace std;

std::shared_ptr<GameBase> GameBase::basePointer = nullptr;

GameBase::GameBase()
{

}

GameBase::GameBase(int wSize, int tSize) // create a function that will instantiate class, scoping here
: wide(wSize), tall(tSize), counterX(0), counterO(0)									 //wide(wSize), tall(tSize){
{
	squares = new GamePiece*[tSize];
	for (int i = 0; i < tSize; i++){
			squares[i] = new GamePiece[wSize];
	}
}

int GameBase::prompt(unsigned int& i, unsigned int &k)
{
	return 0;
}



void GameBase::checkargs(int argc, char * argv[])
{
	//shared_ptr<GameBase> changePoint = basePointer;
	try
	{
		if (basePointer == nullptr)
		{
			if (argc < 2) {
				cout << "Wrong number of arguments entered";
			}

			string argv1(argv[1]);
			if (argv1.compare("TicTacToe") == 0) //.compare used to compare each character 
			{
				basePointer = make_shared<Tictactoegame>(Tictactoegame());
			}
			if (argv1.compare("Gomoku") == 0) //.compare used to compare each character 
			{
				if (argc == 2)
				{
					basePointer = make_shared<GomokuGame>(GomokuGame());
				}
				else if (argc == 3 && isdigit(*argv[2]))
				{
					int size = atoi(argv[2]);
					basePointer = make_shared<GomokuGame>(GomokuGame(size, size));
				}
				else if (argc == 4 && isdigit(*argv[2]) && isdigit(*argv[3]) && (atoi(argv[2]) > atoi(argv[3])))
				{
					int size = atoi(argv[2]);
					int rows = atoi(argv[3]);
					basePointer = make_shared<GomokuGame>(GomokuGame(size, size, rows));
				}
				else
				{
					cout << "Incorrect argument" << endl;
				}
			}
			if (argv1.compare("Sudoku") == 0)
			{
				basePointer = make_shared<SudokuGame>(SudokuGame());
			}
		}
	}
	catch (...)
	{
		cout << "Issue with game pointer" << endl;
	}
	
}

shared_ptr<GameBase> GameBase::instance()
{
	try
	{
		return basePointer;
	}
	catch (...)
	{
		cout << " No game base pointer available" << endl;
	}
}