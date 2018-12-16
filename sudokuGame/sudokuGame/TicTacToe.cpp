
#include "stdafx.h"
#include "TicTacToe.h"

Tictactoegame::Tictactoegame() : GameBase(5, 5)
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

Tictactoegame::Tictactoegame(int wSize, int tSize) // create a function that will instantiate class, scoping here
	: GameBase(wSize, tSize)
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
		cout << "printing tokens" << endl;
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
ostream& operator<<(ostream & out, const Tictactoegame & game) //to print out gameboard
{
	for (int w = game.wide-1; w >= 0; w--) {
		cout << w << " " ;
		for (int t = 0; t < game.tall; t++) {
			out << setw(game.maxString) << game.squares[w][t].display << "\t";
		}
		cout << endl;
	}
	cout << "X ";
	for (int k = 1; k < game.tall; k++) {
		cout << "\t" << k; // use setW to make columns align correctly
	}
	return out;
	// TODO: insert return statement here
}

void Tictactoegame::setTurn()
{
	int xCounter = 0;
	int oCounter = 0;
	for (int i = 0; i < wide; i++)
	{
		for (int j = 0; j < tall; j++)
		{
			if (squares[i][j].display == "X")
				xCounter++;
			if (squares[i][j].display == "O")
				oCounter++;
		}
	}
	if (xCounter <= oCounter)
		whoseTurn = true;
	else
		whoseTurn = false;
}

bool Tictactoegame::done() {
	for (int i = 1; i < wide - 1; i++) {
		if (squares[1][i].display.compare(squares[2][i].display) == 0 && squares[1][i].display.compare(squares[3][i].display) == 0) {
			if (squares[1][i].display.compare("X") == 0) {
				cout << "X won the game" << endl;
				return true;
			}
			else if (squares[1][i].display.compare("O") == 0) {

				cout << "O won the game" << endl;
				return true;
			}
		}
	}
	for (int i = 1; i < tall - 1; i++) {
		if (squares[i][1].display.compare(squares[i][2].display) == 0 && squares[i][1].display.compare(squares[i][3].display) == 0) {
			if (squares[i][1].display.compare("X") == 0) {
				cout << "X won the game" << endl;
				return true;
			}
			else if (squares[i][1].display.compare("O") == 0) {

				cout << "O won the game" << endl;
				return true;
			}
		}
	}

	if (squares[1][1].display.compare(squares[2][2].display) == 0 && squares[1][1].display.compare(squares[3][3].display) == 0) {
		if (squares[1][1].display.compare("X") == 0) {
			cout << "X won the game" << endl;
			return true;
		}
		else if (squares[1][1].display.compare("O") == 0) {

			cout << "O won the game" << endl;
			return true;
		}
	}

	if (squares[3][1].display.compare(squares[2][2].display) == 0 && squares[3][1].display.compare(squares[1][3].display) == 0) {
		if (squares[3][1].display.compare("X") == 0) {
			cout << "X won the game" << endl;
			return true;
		}
		else if (squares[3][1].display.compare("O") == 0) {

			cout << "O won the game" << endl;
			return true;
		}
	}

	return false;
}


bool Tictactoegame::draw() {
	for (int i = 1; i < wide - 1; i++) {
		for (int q = 1; q < tall - 1; q++) {
			if (squares[i][q].display == " " || done() == true) {//open spots remaining
				return false;
			}

		}
	}

	return true;

}

int Tictactoegame::play() {
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

int Tictactoegame::prompt(unsigned int& i, unsigned int & k) {
	string x;
	cout << "Either type 'quit' or enter valid coordinates to play " << endl;
	cin >> x;                                      
	if (x != "quit") {

		if (x.length() == validLength) {

			string a;
			string b;
			int found = x.find(",");
			a = x.substr(0, found);
			b = x.substr(found + 1, x.size());
			istringstream(a) >> i;
			istringstream(b) >> k;
			if (i > 0 && i < wide - 1 && k > 0 && k < tall - 1) {
				if (squares[i][k].display == " ") {
					return trueTurn;
				}

				else {
					cout << "move already taken. try again" << endl;
					prompt(i, k);
					return spotTaken;
				}
			}
			else {
				cout << "coordinate(s) out of bounds" << endl;
				prompt(i, k);
			}
		}

		else {
			cout << "Failure, invalid input. Enter correct coordinates in bounds only." << endl;
			prompt(i, k);
		}
	}
	else {
		cout << "The game will now end." << endl;
		save();
		return exitGame;
	}
	return quit;

}

void Tictactoegame::save()
{
	string response;
	cout << "Do you want to save? (y or n)";
	cin >> response;
	ofstream tictactoefile;
	tictactoefile.open("tictactoe.txt");
	if (response == "n")
	{
		cout << "Game will not be saved." << endl;
		
		tictactoefile << "NO DATA";
		
	}
	else if (response == "y")
	{
		for (int w = wide - 1; w >= 0; w--) 
		{
			for (int t = 0; t < tall; t++) 
			{
				tictactoefile << w << "," << t << "," << squares[w][t].display << "," << squares[w][t].color << endl;
			}
		}
	}
	else
	{
		cout << "Invalid operation. retry" << endl;
		tictactoefile.close();
		save();
	}
	tictactoefile.close();
}

bool Tictactoegame::turn() {
	unsigned int c;
	unsigned int d;
	if (whoseTurn == true) {
		cout << "Player X Turn" << endl;
		if (prompt(c, d) != exitGame) {
			counterX = counterX + 1;
			squares[c][d] = GamePiece(black, "X");
			cout << *this << endl; //print gameboard
			cout << counterX << endl;
			coordinatesX.push_back(to_string(c) + "," + to_string(d));
			for (int c = 0; c < coordinatesX.size(); c++) {
				cout << coordinatesX[c] << endl;
			}
			whoseTurn = false;
			return true;
		}
	}
	else {
		cout << "Player O Turn" << endl;
		if (prompt(c, d) != exitGame) {
			counterO = counterO + 1;
			squares[c][d] = GamePiece(black, "O");
			cout << *this << endl; //print gameboard
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


void Tictactoegame::print()
{
	cout << *this << endl;
}