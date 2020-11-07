#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include"dots.h"
using namespace std;

class board
{
public:
	board(string imageDIrectory,string image) //upload an image from file
	{
		if (!bTexture.loadFromFile(imageDIrectory))
		{
			cerr << "Error\n";
		}
		bSprite.setTexture(bTexture);
		bSprite.setPosition(sf::Vector2f(85.f, 85.f));
		if (!font.loadFromFile(image))
		{
			cerr << "Error\n";
		}
	
		for (int i = 0; i < 7; i++) {
			text1[i].setFont(font);
			text1[i].setString(h[i]);			
			text1[i].setPosition((83*i)+108, 600);
			text2[i].setFont(font);
			text2[i].setString(v[i]);
			text2[i].setPosition(85,(83 * i) + 90);
		}				
	}

	void drawBoard(sf::RenderWindow& window) {
		window.draw(bSprite);
		for (int i = 0; i < 7; i++)
		{
			window.draw(text1[i]);
			window.draw(text2[i]);
		}
	}
	
	bool isvalidPos(int i, int j)
	{
		if (i == j || i == 4 || j == 4 || i + j == 8) return true;
		else return false;
	}
	

	
private:
	
	sf::Texture bTexture;
	sf::Sprite bSprite;
	sf::RenderWindow window;
	sf::Font font;
	sf::Text text1[7];
	sf::Text text2[7];
	string h[7] = {"a","b","c","d","e","f","g"};
	string v[7] = {"7","6","5","4","3","2","1"};
};


