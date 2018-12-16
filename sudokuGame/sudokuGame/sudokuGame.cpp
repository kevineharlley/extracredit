// sudokuGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#pragma once
#include "stdafx.h"
#include "Gomoku.h"
#include "SudokuGame.h"
#define SUDOKUVALIDLENGTH 5

SudokuGame::SudokuGame() 
	: GameBase(9, 9), initialNumbers(80)
{
	for (int i = 0; i < wide; i++)
	{
		for (int j = 0; j < tall; j++)
		{
			squares[i][j] = GamePiece(noColor, " ");
		}
	}
	ifstream myfile("sudoku.txt");
	vector<string> tokens;
	string line;
	int i = 0;
	string token;
	int x;
	int y;
	string display;
	int color;

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			std::stringstream ss(line);
			while (getline(ss, line, ','))
			{
				//cout << line << endl;
				if (line == "NO DATA")
				{
					setupSquares();
					break;
				}
				else
				{
					tokens.push_back(line);
				}
			}
		}
		while (i < tokens.size())
		{
			x = stoi(tokens[i]);
			y = stoi(tokens[i + 1]);
			display = tokens[i + 2];
			color = stoi(tokens[i + 3]);
			GamePiece newPiece = GamePiece(piece_color(color), display);
			squares[x][y] = newPiece;
			i += 4;
		}
	}
	myfile.close();
	
}

bool SudokuGame::done()
{
	for (int i = 0; i < wide; i++) {
		for (int j = 0; j < tall; j++) {
			if (squares[i][j].color == noColor || squares[i][j].color == red)
				return false;
		}
	}
	return true;
}

bool SudokuGame::draw()
{
	return false;
}

void SudokuGame::save()
{
	string response;
	cout << "Do you want to save? (y or n)";
	cin >> response;
	ofstream sudokufile;
	sudokufile.open("sudoku.txt");
	if (response == "n")
	{
		cout << "Game will not be saved." << endl;

		sudokufile << "NO DATA";

	}
	else if (response == "y")
	{
		for (int w = wide - 1; w >= 0; w--)
		{
			for (int t = 0; t < tall; t++)
			{
				sudokufile << w << "," << t << "," << squares[w][t].display << "," << squares[w][t].color << endl;
			}
		}
	}
	else
	{
		cout << "Invalid operation. retry" << endl;
		sudokufile.close();
		save();
	}
	sudokufile.close();
}

void SudokuGame::setupSquares()
{
	srand(time(NULL));
	int randY;
	int randX;
	for (int i = 0; i < initialNumbers;)
	{
		randY = (rand() % 9);
		randX = (rand() % 9);
		string randData = std::to_string(rand() % 9 + 1);
		
		if (isValidPiece(randData, randX, randY))// && squares[randX][randY].display == " ")
		{
			GamePiece randPiece = GamePiece(white, randData);
			squares[randX][randY] = randPiece;
			i++;
		}
	}
}

int SudokuGame::play()
{
	print();
	bool k = turn();
	while (k)
	{
		if (done())
		{
			cout << " Player won the game!" << endl;
			return successPlay;
		}
		if (draw())
		{
			cout << "Board is full but incorrect. Change one of the numbers" << endl;
		}
		k = turn();
	}
	return successPlay;
}

bool SudokuGame::turn()
{
	unsigned int c;
	unsigned int d;
	string k;
	if (prompt(c, d, k) != exitGame)
	{
		cout << *this << endl; //print gameboard
		return true;
	}
	return false;
}

void SudokuGame::print()
{
	cout << *this << endl;
}

int SudokuGame::prompt(unsigned int &xcoordinate, unsigned int &ycoordinate, string &data)
{
	string x;
	cout << "Either type 'quit' or enter valid coordinates to play (x,y,number).*No Spaces " << endl;
	cin >> x;
	if (x != "quit") 
	{
		if (x.length() == SUDOKUVALIDLENGTH) 
		{
			string a;
			string b;
			string c;
			int found = x.find(",");
			a = x.substr(0, found);
			b = x.substr(found+1, found);
			c = x.substr(x.size()-1, x.size());
			istringstream(a) >> xcoordinate;
			istringstream(b) >> ycoordinate;
			data = c;
			//istringstream(c) >> data;
			if (xcoordinate >= 0 && xcoordinate < wide && ycoordinate >= 0 && ycoordinate < tall && stoi(data)< 9) 
			{
				if (squares[xcoordinate][ycoordinate].color == white) 
				{
					cout << "Computer Generated Digit cannot be changed" << endl;
				}
				else
				{
					if (isValidPiece(data, xcoordinate, ycoordinate))
					{
						GamePiece inputPiece = GamePiece(black, data);
						squares[xcoordinate][ycoordinate] = inputPiece;
					}
					else
					{
						GamePiece inputPiece = GamePiece(red, data);
						squares[xcoordinate][ycoordinate] = inputPiece;
					}
				}
			}
			else 
			{
				cout << "coordinate(s) out of bounds" << endl;
				prompt(xcoordinate, ycoordinate, data);
			}
		}
		else 
		{
			cout << "Failure, invalid input. Enter correct coordinates in bounds only." << endl;
			prompt(xcoordinate, ycoordinate, data);
		}
	}
	else 
	{
		cout << "End Game" << endl;
		save();
		return exitGame;
	}
	return trueTurn;
}

ostream &operator<<(ostream &out, const SudokuGame & game)
{
	cout << endl << " =========================================================================" << endl;
	for (int w = game.tall - 1; w >= 0; w--) {
		cout << w << "||\t";
		for (int t = 0; t < game.wide; t++) {
			if (game.squares[w][t].color != noColor)
			{
				out << game.squares[w][t].display << "|\t";
			}
			else if (((t+1) % 3) == 0)
				cout << "||\t";
			else
			{
				out << " |\t";
			}
			
		}
		if ((w % 3) == 0)
		{
			cout << endl << " =========================================================================" << endl;
		}
		else
		{
			cout << endl << " -------------------------------------------------------------------------" << endl;
		}
	}
	cout << "X";
	for (int k = 0; k < game.tall; k++) {
		if (k % 3 == 0)
			cout << "||";
		cout << "\t" << k; // use setW to make columns align correctly
	}
	return out;
	// TODO: insert return statement here
}

bool SudokuGame::isValidPiece(string data, int xcoordinate, int ycoordinate)
{
	for (int i = 0; i < wide; i++)
	{
		if (i != xcoordinate)
		{
			if (squares[i][ycoordinate].display == data && (squares[i][ycoordinate].color == black || squares[i][ycoordinate].color == white))
				return false;
		}
	}
	for (int j = 0; j < tall; j++)
	{
		if (j != ycoordinate)
		{
			if (squares[xcoordinate][j].display == data && (squares[xcoordinate][j].color == black || squares[xcoordinate][j].color == white))
				return false;
		}
	}
	int boxesLeft = xcoordinate % 3;
	int boxesRight = 2-boxesLeft;
	int boxesDown = ycoordinate % 3;
	int boxesUp = 2-boxesDown;
	for (int i = 1; i <= boxesLeft; i++)
	{
		for (int k = 1; k <= boxesDown; k++)
		{
			if (squares[xcoordinate-i][ycoordinate - k].display == data && (squares[xcoordinate - i][ycoordinate - k].color == black || squares[xcoordinate - i][ycoordinate - k].color == white))
				return false;
		}
		for (int l = 1; l <= boxesUp; l++)
		{
			if (squares[xcoordinate-i][ycoordinate + l].display == data && (squares[xcoordinate - i][ycoordinate + l].color == black || squares[xcoordinate - i][ycoordinate + l].color == white))
				return false;
		}
	}
	for (int j = 1; j <= boxesRight; j++)
	{
		for (int k = 1; k <= boxesDown; k++)
		{
			if (squares[xcoordinate + j][ycoordinate - k].display == data && (squares[xcoordinate + j][ycoordinate - k].color == black || squares[xcoordinate + j][ycoordinate - k].color == white))
				return false;
		}
		for (int l = 1; l <= boxesUp; l++)
		{
			if (squares[xcoordinate + j][ycoordinate + l].display == data && (squares[xcoordinate + j][ycoordinate + l].color == black || squares[xcoordinate + j][ycoordinate + l].color == white))
				return false;
		}
	}
	
	return true;
}