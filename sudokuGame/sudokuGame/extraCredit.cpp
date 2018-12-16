#include "stdafx.h"
#include <iostream>
#include "GameBase.h"
using namespace std;



int usageMessage(string cstr) {

	cout << cstr << endl;

	return Success;

	if (sizeof(cstr) != 2) {

		return fileNotOpen;

	}
}

int main(int argc, char * argv[]) {
	try
	{
		//GameBase *setup = new GameBase();
		//setup
		std::shared_ptr<GameBase> nGameBase;
		nGameBase->checkargs(argc, argv);
		std::shared_ptr<GameBase> testBase = nGameBase->instance();
		if (!testBase) { //singular, the pointer is invalid, null

			cout << usageMessage(argv[0]) << endl;

		}

		else {

			//GameBase T();

			testBase->play();

		}
		//declaring an object of the TicTacToe game
		return 0;
	}
	catch (...)
	{
		cout << "Exception caught" << endl;
		return 1;
	}
	

}