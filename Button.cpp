#include "Button.h"

Button::Button(std::string name, float sizeX, float sizeY, float posX, float posY, int fontSize, sf::Color buttonColor) { //constructor takes the name of the button which will be written on the button, and the width(x) and height(y) of the button as a rectangle shape, and the x and y position of the rectangle
	if (!font.loadFromFile("NotoSansJP-Black.otf")) {
		std::cout << "Cannot find the font file 'NotoSansJP-Black.otf' make sure it is in the same folder as NineManGame.cpp" << std::endl;
	}

	buttonBox.setSize(sf::Vector2f(sizeX, sizeY));
	buttonBox.setPosition(posX, posY);
	buttonBox.setFillColor(buttonColor);

	buttonText.setFont(font);
	buttonText.setString(name);
	buttonText.setCharacterSize(fontSize);
	buttonText.setPosition(posX + ((sizeX - buttonText.getLocalBounds().width) / 2), posY + ((sizeY - buttonText.getLocalBounds().height) / 2));//+ ((posY - buttonText.getLocalBounds().top) / 2));
	buttonText.setOutlineColor(sf::Color::Black);
	buttonText.setOutlineThickness(3);

}

Button::~Button() {

}

bool Button::clicked(sf::Event & event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left && buttonBox.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
			return true;
		}
	}
	return false;
}

void Button::draw(sf::RenderWindow & window) {
	window.draw(buttonBox);
	window.draw(buttonText);
}