#pragma once
#include <SFML/Graphics.hpp>

class StartWindow {
public:
	void runWindow();
	StartWindow();
	~StartWindow();

private:
	sf::RenderWindow window;
	sf::RectangleShape button;

};