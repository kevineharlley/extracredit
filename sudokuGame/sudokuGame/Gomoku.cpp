#pragma once
#include "stdafx.h"
#include "Gomoku.h"
#define zero 0

GomokuGame::GomokuGame() : GameBase(19,19 ), winRows(5)
{
	ifstream myfile("gomoku.txt");
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
					for (int i = 0; i < wide; i++)
					{
						for (int j = 0; j < tall; j++)
						{
							squares[i][j] = GamePiece(noColor, " ");
						}
					}
					break;
				}
				else
				{
					tokens.push_back(line);
				}
			}
		}
		//cout << "printing tokens" << endl;
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
		setTurn();
	}
	myfile.close();
}

GomokuGame::GomokuGame(const GomokuGame& oldGame)
{
	wide = oldGame.wide;
	tall = oldGame.tall;
	counterO = oldGame.counterO;
	counterX = oldGame.counterX;

	coordinatesO = oldGame.coordinatesO;
	coordinatesX = oldGame.coordinatesX;
	whoseTurn = oldGame.whoseTurn;
	maxString = oldGame.maxString;
	winRows = oldGame.winRows;

	GamePiece** testSquares;
	testSquares = new GamePiece*[wide];
	for (int i = 0; i < wide; i++) {
		testSquares[i] = new GamePiece[wide];
	}

	for (int i = zero; i < wide; i++)			//makes copy of original array to new array (to test if there's a draw)
	{
		for (int j = zero; j < wide; j++)
		{
			testSquares[i][j] = oldGame.squares[i][j];
		}
	}
	squares = testSquares;
}

GomokuGame::GomokuGame(int wSize, int tSize) : GameBase(wSize, tSize), winRows(5)
{
	ifstream myfile("tictactoe.txt");
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
					for (int i = 0; i < wide; i++)
					{
						for (int j = 0; j < tall; j++)
						{
							squares[i][j] = GamePiece(noColor, " ");
						}
					}
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
		setTurn();
	}
	myfile.close();
}

void GomokuGame::setTurn()
{
	int bCounter = 0;
	int wCounter = 0;
	for (int i = 0; i < wide; i++)
	{
		for (int j = 0; j < tall; j++)
		{
			if (squares[i][j].display == "B")
				bCounter++;
			if (squares[i][j].display == "W")
				wCounter++;
		}
	}
	if (bCounter <= wCounter)
		whoseTurn = true;
	else
		whoseTurn = false;
}

int GomokuGame::play() {
	print();
	bool k = turn();
	while (k == true) {
		//print();
		if (done() == true) {
			cout << " Player won the game!" << endl;
			return successPlay;
		}
		if (draw() == true) {
			cout << "X had " << counterX << " moves and O had " << counterO << " moves." << endl;
			cout << "No winning moves remain" << endl;
			return failure;
		}
		k = turn();
	}
	return failurePlay;
}

GomokuGame::GomokuGame(int wSize, int tSize, int newRows) : GameBase(wSize, tSize)
{
	for (int i = 0; i < wide; i++) {
		for (int j = 0; j < tall; j++) {
			squares[i][j] = GamePiece(noColor, " ");
		}
	}
	winRows = newRows;
}

int GomokuGame::prompt(unsigned int & i, unsigned int & k)
{
	string x;
	cout << "Either type 'quit' or enter valid coordinates to play " << endl;
	cin >> x;
	if (x == "quit" || x == "Quit") {		//checks if user input 'quit'
		cout << "The game will now end." << endl;
		save();
		return exitGame;
	}
	else if (x != "quit" || x != "Quit") {

		string a;
		string b;
		int found = x.find(",");				//parse on comma
		a = x.substr(zero, found);				//first half before comma
		b = x.substr(found + 1, x.size());	//second half after comma
		istringstream(a) >> i;
		istringstream(b) >> k;


		if (i > zero && i <= wide && k > zero && k <= tall) 
		{
			if (squares[i - 1][k - 1].display == " ") 
			{			//turn can be done if it is empty. else it's taken.
				return trueTurn;
			}

			else {
				cout << "move already taken. try again" << endl;
				prompt(i, k);
				return spotTaken;
			}
		}
		else 
		{
			cout << "coordinate(s) not in valid bounds" << endl;
			prompt(i, k);
		}
	}
	return quit;

}

void GomokuGame::save()
{
	string response;
	cout << "Do you want to save? (y or n)";
	cin >> response;
	ofstream gomokufile;
	gomokufile.open("gomoku.txt");
	if (response == "n")
	{
		cout << "Game will not be saved." << endl;

		gomokufile << "NO DATA";

	}
	else if (response == "y")
	{
		for (int w = wide - 1; w >= 0; w--)
		{
			for (int t = 0; t < tall; t++)
			{
				gomokufile << w << "," << t << "," << squares[w][t].display << "," << squares[w][t].color << endl;
			}
		}
	}
	else
	{
		cout << "Invalid operation. retry" << endl;
		gomokufile.close();
		save();
	}
	gomokufile.close();
}


bool GomokuGame::done()
{ 

	bool match = true;

	//horizontal
	for (int row = 0; row < tall; row++) {
		for (int col = 0; col < wide-winRows; col++){
			match = true;
			for (int i = 0; i < winRows; i++) {
				int test = (squares[row][col].display).compare(" ");
				bool test2 = (squares[row][col + i].display) != squares[row][col].display;
				if ((squares[row][col + i].display) != squares[row][col].display || (squares[row][col].display).compare(" ") == 0) {
					match = false;
				}
			}
			if (match == true)
			{
				return true;
			}

		}
	}
	
	
	  
	//vertical
		for (int row = tall-1; row >=  winRows-1; row--) { // change to wide - 5
			for (int col = 0; col < wide; col++)
			{
				match = true;
				for (int i = 0; i < winRows; i++) {
					if ((squares[row - i][col].display) != squares[row][col].display || (squares[row][col].display).compare(" ") == 0) {
						match = false;
					}
				}
				if (match == true)
				{
					return true;
				}
			}
		}

	//diagonal - from left
		for (int row = tall-1; row >= winRows-1; row-- ){
			for (int col = 0; col <= wide-winRows; col++)
			{
				match = true;
				for (int i = 0; i < winRows; i++) {
					if ((squares[row - i][col + i].display) != squares[row][col].display || (squares[row][col].display).compare(" ") == 0) {
						match = false;
					}
				}
				if (match == true)
				{
					return true;
				}
			}
		}
		//diagonal - from right
		for (int row = tall - 1; row >= winRows - 1; row--) {
			for (int col = winRows-1; col < wide; col++)
			{
				match = true;
				for (int i = 0; i < winRows; i++) {
					if ((squares[row - i][col - i].display) != (squares[row][col].display) != 0 || (squares[row][col].display).compare(" ") == 0) {
						match = false;
					}
				}
				if (match == true)
				{
					return true;
				}
			}
		}
		return match;
}

bool GomokuGame::draw()
{
	GomokuGame drawTest = GomokuGame(*this);
	drawTest.fillSquares();
	bool isDraw = !drawTest.done();
	return isDraw;
	//return false;
}

void GomokuGame::fillSquares()
{
	if (whoseTurn == true)
	{
		for (int i = 0; i < wide; i++)
		{
			for (int j = 0; j < wide; j++)
			{
				if (squares[i][j].display.compare(" ") == 0)
				{
					squares[i][j] = GamePiece(black, " B");
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < wide; i++)
		{
			for (int j = 0; j < wide; j++)
			{
				if (squares[i][j].display.compare(" ") == 0)
				{
					squares[i][j] = GamePiece(black, "W");
				}
			}
		}
	}
}

bool GomokuGame::turn()
{
	unsigned int c;
	unsigned int d;

	if (whoseTurn == true) {
		cout << "Black Stone" << endl;
		if (prompt(c, d) != exitGame) {
			counterX = counterX + 1;
			squares[c-1][d-1] = GamePiece(black, "B");
			cout << *this;
			cout << "This is x turn " << counterX << endl;
			coordinatesX.push_back(to_string(c) + "," + to_string(d));
			for (int c = 0; c < coordinatesX.size(); c++) {
				cout << coordinatesX[c] << endl;
			}
			whoseTurn = false;
			return true;
		}
	}
	else {
		cout << "White Stone" << endl;
		if (prompt(c, d) != exitGame) {
			counterO = counterO + 1;
			squares[c-1][d-1] = GamePiece(black, "W");
			cout << *this;
			cout << counterO << endl;
			coordinatesO.push_back(to_string(c) + "," + to_string(d));
			for (int i = 0; i <coordinatesO.size(); i++) {
				cout << coordinatesO[i] << endl;
			}
			whoseTurn = true;
			return true;
		}
	}
	return false;

}

void GomokuGame::print()
{
	cout << *this << endl;
}

ostream & operator<<(ostream & out, const GomokuGame & game)
{	
	for (int i = game.tall; i > 0; i--) {
		cout << i;

		for (int j = 0; j < game.tall; j++) {
			//out << "X"; 
			//out << squares[i][j].display << " "; 
			if (j > 10) {
				out << setw(3) << game.squares[j][i-1].display;
			}
			else {
				out << setw(2) << game.squares[j][i-1].display;
			}

		}
		cout << endl;
	}

	cout << "X";
	for (int k = 1; k <= game.tall; k++) {
		cout << " "<<  k; // use setW to make columns align correctly
		
	}
	cout << endl;

	return out;
}