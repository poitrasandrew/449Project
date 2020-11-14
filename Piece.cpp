#include "Piece.h"

void Piece::setCoordinates(int x, int y) {
	xCoord = x;
	yCoord = y;

	// TODO: convert to and set backend coordinates as well, ensure row/columns match y/x

}

void Piece::setTempCoordinates(int tempX, int tempY) {
	tempXCoord = tempX;
	tempYCoord = tempY;

	// TODO: convert to and set temp backend coordinates as well, ensure row/columns match y/x
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

int Piece::getTempRow() {
	return tempRow;
}

int Piece::getTempCol() {
	return tempCol;
}

Piece::Piece(float size, float i, float j, sf::Color color) {
	pieceShape = pieceShapeGenerator(size, i, j, color);
}

sf::CircleShape Piece::pieceShapeGenerator(float size, float i, float j, sf::Color color) {
	// returns shape to be drawn on board
	pieceShape.setRadius(size);
	pieceShape.setFillColor(color);
	pieceShape.setPosition(i, j);

	setCoordinates(i, j);
	return pieceShape;
}

void Piece::drawPieces(sf::RenderWindow& window, std::vector<Piece> &pieces) {
	for (int i = 0; i < pieces.size(); i++)
		window.draw(pieces[i].pieceShape);
}

Piece::~Piece() {
}
