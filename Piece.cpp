#include "Piece.h"

void Piece::setCoordinates() {
	xCoord = pieceShape.getPosition().x;
	yCoord = pieceShape.getPosition().y;

	convertCoordinates();		// sets backend coordinates

}

void Piece::setTempCoordinates(int tempR, int tempC) {
	tempRow = tempR;
	tempCol = tempC;
}

void Piece::setBoardCoordinates(int row, int col) {
	BoardRow = row;
	BoardCol = col;
}

bool Piece::isPlaced() {
	return placed;
}

void Piece::setPlaced() {
	placed = true;
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

	setCoordinates();
	return pieceShape;
}

void Piece::drawPieces(sf::RenderWindow& window, std::vector<Piece> &pieces) {
	for (int i = 0; i < pieces.size(); i++)
		window.draw(pieces[i].pieceShape);
}

void Piece::snapToNewPos() {//uses the backend row and column to snap the piece to the center of its frontend window "grid coordinate"
	xCoord = 99 + (BoardCol * 82);
	yCoord = 99 + (BoardRow * 82);
	pieceShape.setOrigin(0,0);
	pieceShape.setPosition(xCoord, yCoord);
}

void Piece::snapToOldPos() {//meant to snap the piece to its old frontend grid coordinate which will be held in the temp variables for use when an invalid move is attempted
	pieceShape.setOrigin(0,0);
	pieceShape.setPosition(xCoord, yCoord);
}


void Piece::convertCoordinates() { //set up for 720x720 window with board at 85,85

	BoardCol = ((pieceShape.getPosition().x - 73) / 82);//sets backend row and col with 0 as first position and 6 as last position
	BoardRow = ((pieceShape.getPosition().y - 73) / 82);

	if (BoardCol < 0 || BoardCol > 6) {//if out of range of the board then the x and y positions are both set to -1
		BoardCol = -1;
		BoardRow = -1;
	}
	else if (BoardRow < 0 || BoardRow > 6) {
		BoardCol = -1;
		BoardRow = -1;
	}
}

void Piece::convertTempCoordinates() { //set up for 720x720 window with board at 85,85

	tempCol = ((pieceShape.getPosition().x - 73) / 82);//sets backend row and col with 0 as first position and 6 as last position
	tempRow = ((pieceShape.getPosition().y - 73) / 82);

	if (tempCol < 0 || tempCol > 6) {//if out of range of the board then the x and y positions are both set to -1
		tempCol = -1;
		tempRow = -1;
	}
	else if (tempRow < 0 || tempRow > 6) {
		tempCol = -1;
		tempRow = -1;
	}
}

Piece::~Piece() {
}
