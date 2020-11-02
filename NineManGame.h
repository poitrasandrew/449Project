#include <SFML/Graphics.hpp>
#include <iostream>

#pragma once
class NineManGame
{
public:
	static const int ROWMAX = 7, COLMAX = 7, ROWMIN = 0, COLMIN = 0;	// edge array positions
	static const int INVALID = -1, EMPTY = 0, WHITE = 1, BLACK = 2;		// array value definitions

	void runWindow();
private:
	sf::RenderWindow window;
	void drawBoard(std::string);
	sf::RectangleShape square;
	sf::CircleShape dot;
	sf::Texture bTexture;
	sf::Sprite bSprite;
};