#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "Board.h"
#include "BackendBoard.h"
#include "Piece.h"
#include "Button.h"

#pragma once
class NineManGame
{
public:
	static const int ROWMAX = 7, COLMAX = 7, ROWMIN = 0, COLMIN = 0;	// edge array positions
	static const int INVALID = -1, EMPTY = 0, WHITE = 1, BLACK = 2;		// array value definitions
	static std::string getcolorString(int i);

	void runWindow(int goesFirst);
	void changeTurn(int &currentTurn);
	void displayTurn(int &currentTurn);
	void declareWinner(char winner);
private:
	sf::RenderWindow window;
	sf::RectangleShape square;
	sf::CircleShape dot;
	sf::Texture bTexture;
	sf::Sprite bSprite;
	int turn;							// track player turn	
};
