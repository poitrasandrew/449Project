#include "NineManGame.h"
#include "BackendBoard.h"

void NineManGame::runWindow() {
	BackendBoard backend = BackendBoard();	// create object for backend logic handling
	window.create(sf::VideoMode(550, 550), "9 Men's Morris");

	window.setFramerateLimit(60);


	sf::CircleShape white1(20.f);
	white1.setFillColor(sf::Color::White);
	white1.setPosition(sf::Vector2f(360.f, 360.f));

	bool selected = false;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			//end loop when window closes
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			//chnages origin of the moved dot to make dragging more intuitive on left click
			else if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (white1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
						white1.setOrigin(event.mouseButton.x - (white1.getPosition().x - white1.getOrigin().x),
							event.mouseButton.y - (white1.getPosition().y - white1.getOrigin().y));
						selected = !selected;
					}
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					selected = !selected;		// stop dragging piece on mouse release
												// function calls to check for valid position
					backend.printBoard();		// print updated backend board for console logging
				}
			}

			//moves the dot around when one has been selected
			if (selected) {
				white1.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
			}
		}
		window.clear();
		drawBoard("board.png");
		window.draw(bSprite);
		window.draw(white1);
		window.display();
	}
	return;
}

void NineManGame::drawBoard(std::string imageDirectory)
{
	if (!bTexture.loadFromFile(imageDirectory))
	{
		std::cerr << "Error\n";
	}
	bSprite.setTexture(bTexture);
	//bSprite.setPosition(sf::Vector2f(35.f, 35.f));


}