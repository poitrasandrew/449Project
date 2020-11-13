#include "Piece.h"

 sf::CircleShape Piece::pcs(float size, float i, float j, sf::Color col) {
	sf::CircleShape p;
	p.setRadius(size);
	p.setFillColor(col);
	p.setPosition(i, j);
	return p;
}

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
void Piece::drawDots(sf::RenderWindow& window, vector< sf::CircleShape> pcs)
{
	for (int i = 0; i < pcs.size(); i++)
		window.draw(pcs[i]);
}