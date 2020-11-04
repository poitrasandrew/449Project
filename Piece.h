#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Piece {

public:
	Piece(sf::Color);

	void setCoordinates(int x, int y);	// needs to convert/set backend coordinates as well
	int getX();
	int getY();
	int getBoardRow();
	int getBoardCol();
	bool isInMill = false;

private:
	int xCoord;		// GUI coordinates
	int yCoord;
	int BoardRow;	// backend "coordinates"
	int BoardCol;
 };