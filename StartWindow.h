#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

class StartWindow {
public:
	void runWindow();
	StartWindow();
	~StartWindow();

private:
	sf::RenderWindow window;

};