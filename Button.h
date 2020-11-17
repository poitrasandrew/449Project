#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Button {//class used to make clickable buttons for game options eg: start window options, replay option,...
public:
	Button(std::string name, float sizeX, float sizeY, float posX, float posY, int fontSize, sf::Color buttonColor);//constructor takes the name of the button which will be written on the button, and the width(x) and height(y) of the button as a rectangle shape, and the x and y position of the rectangle
	~Button();
	bool clicked(sf::Event &);
	void draw(sf::RenderWindow &);
	sf::RectangleShape buttonBox;
	sf::Text buttonText;

private:
	
	sf::Font font;
};