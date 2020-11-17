#pragma once

#include <SFML/Graphics.hpp>
#include "NineManGame.h"
#include "Button.h"

class FirstTurnWindow {
public:
	FirstTurnWindow();
	~FirstTurnWindow();
	static const int WHITE = 1, BLACK = 2;
	void runWindow();

private:
	sf::RenderWindow window;

};