#include "Piece.h"

void Piece::setCoordinates(int x, int y) {
	xCoord = x;
	yCoord = y;

	// convert to backend coordinates as well, ensure row/columns match y/x
}

int Piece::getX() {
	return xCoord;
}

int Piece::getY() {
	return yCoord;
}

int Piece::getBoardRow() {
	return BoardRow;
}

int Piece::getBoardCol() {
	return BoardCol;
}
