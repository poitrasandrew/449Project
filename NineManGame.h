#include <SFML/Graphics.hpp>
#include <iostream>

#pragma once
class NineManGame
{
public:
	void runWindow();
private:
	sf::RenderWindow window;
	void drawBoard(std::string);
	sf::RectangleShape square;
	sf::CircleShape dot;
	sf::Texture bTexture;
	sf::Sprite bSprite;
};