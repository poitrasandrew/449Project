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

void Piece::convertCoordinates() { //set up for 720x720 window with board at 85,85

	BoardCol = (pieceShape.getPosition().x - 73 / 82);//sets backend row and col with 0 as first position and 6 as last position
	BoardRow = (pieceShape.getPosition().y - 73 / 82);

	if (BoardCol < 0 || BoardCol > 6) {//if out of range of the board then the x and y positions are both set to -1
		BoardCol = -1;
		BoardRow = -1;
	}
	else if (BoardRow < 0 || BoardRow > 6) {
		BoardCol = -1;
		BoardRow = -1;
	}
}

Piece::~Piece() {
}
