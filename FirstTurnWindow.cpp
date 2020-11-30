#include "FirstTurnWindow.h""

FirstTurnWindow::FirstTurnWindow() {

}

FirstTurnWindow::~FirstTurnWindow() {

}

void FirstTurnWindow::runWindow() {
	window.create(sf::VideoMode(400.f, 300.f), "Who Goes First?");
	window.setFramerateLimit(60);

	sf::RectangleShape gameBackground(sf::Vector2f(400.f, 300.f));		// Create a solid color background that will go behind the game board
	gameBackground.setFillColor(sf::Color(140, 140, 140, 255));
	gameBackground.setPosition(sf::Vector2f(0.f, 0.f));

	Button white("White Goes First", 300, 50, 50.f, 50.f, 30, sf::Color::Transparent);
	Button black("Black Goes First", 300, 50, 50.f, 150.f, 30, sf::Color::Transparent);

	NineManGame game;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (white.clicked(event)) {
				window.close();
				game.runWindow(NineManGame::WHITE);
			}
			if (black.clicked(event)) {
				window.close();
				game.runWindow(NineManGame::BLACK);
			}
		}

		window.clear();

		window.draw(gameBackground);
		white.draw(window);
		black.draw(window);

		window.display();

	}
	return;
}