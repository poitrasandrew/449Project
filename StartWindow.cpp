#include "StartWindow.h"

StartWindow::StartWindow() {

}

StartWindow::~StartWindow() {

}

void StartWindow::runWindow() {
	window.create(sf::VideoMode(400, 300), "Mill Game Options");
	window.setFramerateLimit(60);
	

	Button pvp("2 Player Game", 300, 50, 50.f, 50.f, 30, sf::Color::Magenta);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		pvp.draw(window);

	}
}