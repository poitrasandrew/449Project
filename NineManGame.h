#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include<iostream>
using namespace std;
class NineManGame
{
public:
	NineManGame(std::string , std::string ); //upload an image from file and the font 
	static const int ROWMAX = 7, COLMAX = 7, ROWMIN = 0, COLMIN = 0;	// edge array positions
	static const int INVALID = -1, EMPTY = 0, WHITE = 1, BLACK = 2;		// array value definitions
	static std::string getcolorString(int i);
	void drawBoard(sf::RenderWindow& window);
	void runWindow();
private:
	
	sf::RenderWindow window;
	sf::RectangleShape square;
	sf::CircleShape dot;
	sf::Texture bTexture;
	sf::Sprite bSprite;
	sf::Font font;
	sf::Text text1[7];
	sf::Text text2[7];
	std::string h[7] = { "a","b","c","d","e","f","g" };
	std::string v[7] = { "7","6","5","4","3","2","1" };
};