#pragma once
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

class Board
{
public:
	Board();
	Board(std::string imageDirectory, std::string image);
	void drawBoard(sf::RenderWindow& window);
	~Board();

private:
	sf::Texture bTexture;
	sf::Sprite bSprite;
	sf::RenderWindow window;
	sf::Font font;
	sf::Text text1[7];
	sf::Text text2[7];
	std::string h[7] = { "a","b","c","d","e","f","g" };
	std::string v[7] = { "7","6","5","4","3","2","1" };
};

