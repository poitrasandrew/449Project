#include "StartWindow.h"
#include "FirstTurnWindow.h"

StartWindow::StartWindow() {

}

StartWindow::~StartWindow() {

}

void StartWindow::runWindow() {
	window.create(sf::VideoMode(400.f, 300.f), "Mill Game Options");
	window.setFramerateLimit(60);
	
	sf::RectangleShape gameBackground(sf::Vector2f(400.f, 300.f));		// Create a solid color background that will go behind the game board
	gameBackground.setFillColor(sf::Color(140, 140, 140, 255));
	gameBackground.setPosition(sf::Vector2f(0.f, 0.f));

	Button pvpButton("2 Player Game", 300, 50, 50.f, 50.f, 30, sf::Color::Transparent);
	Button pveButton("1 Player Game", 300, 50, 50.f, 150.f, 30, sf::Color::Transparent);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (pvpButton.clicked(event)) {
				window.close();
				FirstTurnWindow ftw;
				ftw.runWindow();
			}
		}

		window.clear();

		window.draw(gameBackground);
		pvpButton.draw(window);
		pveButton.draw(window);

		window.display();

	}
	return;
}