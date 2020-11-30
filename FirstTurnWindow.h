#pragma once

#include <SFML/Graphics.hpp>
#include "NineManGame.h"
#include "Button.h"

class FirstTurnWindow {
public:
	FirstTurnWindow();
	~FirstTurnWindow();
	void runWindow();

private:
	sf::RenderWindow window;

};