#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include<vector>
using namespace std;
class Piece {

public:
	//Piece( sf::Color);
	sf::CircleShape pcs(float size, float i, float j, sf::Color col);
	void setCoordinates(int x, int y);	// needs to convert/set backend coordinates as well
	int getX();
	int getY();
	int getBoardRow();
	int getBoardCol();
	void drawDots(sf::RenderWindow& window, vector< sf::CircleShape> pcs);

	bool isInMill = false;

private:
	int xCoord;		// GUI coordinates
	int yCoord;
	int BoardRow;	// backend "coordinates"
	int BoardCol;
	vector<sf::CircleShape>vec;

 };