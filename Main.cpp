#include <SFML/Graphics.hpp>
#include "NineManGame.h"

int main()
{
	sf::RenderWindow window;
	NineManGame mygame("board.png", "theimage.ttf");
	mygame.runWindow();
}
