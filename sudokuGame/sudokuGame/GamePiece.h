#pragma once
//GamePiece.h

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include<sstream>
#include <locale>

#ifndef GAMEPIECE_H
#define GAMEPIECE_H
#endif // !GAMEPIECE_H

using namespace std;


enum piece_color { red, black, white, invalidColor, noColor };
string pcol(piece_color);
piece_color colorConverter(string);


struct GamePiece {
	GamePiece();
	GamePiece(piece_color, string);
	piece_color color;
	string display;
};
