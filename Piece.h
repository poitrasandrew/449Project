#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include<vector>
using namespace std;
class Piece {

public:

	Piece(float size, float i, float j, sf::Color color);
	sf::CircleShape pieceShape;
	sf::CircleShape pieceShapeGenerator(float size, float i, float j, sf::Color color);
	static void drawPieces(sf::RenderWindow& window, std::vector<Piece> &pieces);
	void setCoordinates(int x, int y);	// needs to convert/set backend coordinates as well
	void setTempCoordinates(int tempX, int tempY);
	void convertCoordinates();
	void snapToNewPos();
	void snapToOldPos();
	int getX();
	int getY();
	int getTempRow();
	int getTempCol();
	int getBoardRow();
	int getBoardCol();
	~Piece();

private:
	int xCoord;		// GUI coordinates
	int yCoord;
	int tempXCoord;
	int tempYCoord;

	int BoardRow;	// backend "coordinates"
	int BoardCol;
	int tempRow;
	int tempCol;
 };