#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
using namespace std;
class board 
{
public:
	board(string imageDIrectory) 
	{
		if (!bTexture.loadFromFile(imageDIrectory))
		{
			cerr << "Error\n";
		}
		bSprite.setTexture(bTexture);
		//bSprite.setPosition(sf::Vector2f(35.f, 35.f));
		
		
	}
	board(sf::Vector2f size, float x, float y)
	{
		theboard.setSize(size);
		theboard.setFillColor(sf::Color::Transparent);
		theboard.setFillColor(sf::Color::Transparent);
		theboard.setOutlineThickness(10.f);
		theboard.setOutlineColor(sf::Color::Yellow);
		theboard.setPosition(sf::Vector2f(x, y));
		
	}
	

	void drawPlayer(sf::RenderWindow& window) {
		//window.draw(bSprite);
		window.draw(theboard);
		
	}
private:
	sf::RectangleShape theboard;
	sf::Vertex line[4];
	sf::Texture bTexture;
	sf::Sprite bSprite;
	
};
