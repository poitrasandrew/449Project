#include "Board.h"

Board::Board(std::string imageDirectory, std::string image) //upload an image from file
{
	if (!bTexture.loadFromFile(imageDirectory))
	{
		std::cout << "Error loading board image file." << std::endl;
	}
	bSprite.setTexture(bTexture);
	bSprite.setPosition(sf::Vector2f(85.f, 85.f));
	if (!font.loadFromFile(image))
	{
		std::cout << "Error loading board text font file." << std::endl;
	}

	for (int i = 0; i < 7; i++) {
		text1[i].setFont(font);
		text1[i].setString(h[i]);
		text1[i].setPosition((83 * i) + 108, 600);
		text2[i].setFont(font);
		text2[i].setString(v[i]);
		text2[i].setPosition(85, (83 * i) + 90);
	}
}

void Board::drawBoard(sf::RenderWindow& window) {
	window.draw(bSprite);
	for (int i = 0; i < 7; i++)
	{
		window.draw(text1[i]);
		window.draw(text2[i]);
	}
}

Board::Board() {
}
Board::~Board(){
}
