#include "stdafx.h"
#include "GamePiece.h"

GamePiece::GamePiece()
{
	color = noColor;
	display = " ";
}

GamePiece::GamePiece(piece_color p, string display)
	: color(p), display(display) {}
string pcol(piece_color c) {
	if (c == piece_color::red) {
		return "red";
	}
	if (c == piece_color::black) {
		return "black";
	}
	if (c == piece_color::white) {
		return "white";
	}
	return "invalidColor";
}

piece_color colorConverter(string color) {
	if (color == "red") {
		return red;
	}
	if (color == "black") {
		return black;
	}

	if (color == "white") {
		return white;
	}
	if (color.empty() == true) {
		return noColor;
	}

	return invalidColor;
}