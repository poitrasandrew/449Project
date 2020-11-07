#include <SFML/Graphics.hpp>
#include "boarb.h"
#include"dots.h"
#include<iostream>
#include<vector>
using namespace std;
void runWindow();
    int main(){
  
	runWindow();
	return 0;

	}
	
void runWindow()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(720, 720), "9 Men's Morris");
	window.setFramerateLimit(60);
	dot pc;
	//int turn = 1; // 
	vector<sf::CircleShape> white, red,player;
	for (int i = 0; i < 18; i = i +2)
	{
		red.push_back(pc.pcs(15.f, (i + 1) * 20, 17, sf::Color::Yellow));
		white.push_back(pc.pcs(15.f,(i+1)*20, 50,sf::Color::Red));
	}
	//player = white;
	board myBrd("main.png","theimage.ttf");
	bool selected = false;
	int n = 0;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {

			//end loop when window closes
			if (event.type == sf::Event::Closed)
				window.close();
			//chnages origin of the moved dot to make dragging more intuitive on left click 
			//and releases dot when left click is released
			if (sf::Event::MouseButtonPressed)
				if (event.mouseButton.button == sf::Mouse::Left)
					for (int i = 0; i < white.size(); i++) {

						if (white[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
							selected = true; n = i;
							white[i].setOrigin(event.mouseButton.x - (white[i].getPosition().x - white[i].getOrigin().x),
								event.mouseButton.y - (white[i].getPosition().y - white[i].getOrigin().y));

						}
					}
			if (event.type == sf::Event::MouseButtonReleased)
				if (event.key.code == sf::Mouse::Left)
					selected = false;



			//moves the dot around when one has been selected
			if (selected) {
				white[n].setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
			}
		}

		window.clear();
		myBrd.drawBoard(window);
		pc.drawDots(window, white);
		pc.drawDots(window, red);
		window.display();
	}
}
		
	


