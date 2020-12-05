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
	void setCoordinates();
	void setTempCoordinates(int tempR, int tempC);
	void setBoardCoordinates(int row, int col);
	void convertCoordinates();
	void convertTempCoordinates();
	void snapToNewPos();
	void snapToOldPos();
	int getX();
	int getY();
	int getTempRow();
	int getTempCol();
	int getBoardRow();
	int getBoardCol();
	bool isPlaced();
	void setPlaced();
	~Piece();

private:
	float xCoord;	// GUI coordinates
	float yCoord;
	int tempXCoord;
	int tempYCoord;

	int BoardRow;	// backend "coordinates"
	int BoardCol;
	int tempRow;
	int tempCol;

	bool placed = false;	// track which pieces have been placed
 };