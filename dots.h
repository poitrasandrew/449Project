#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include"boarb.h"
#include<vector>
using namespace std;
class dot
{
public:
    sf::CircleShape pcs(float size, float i,float j,sf::Color col ) {
        p.setRadius(size);
        p.setFillColor(col);
        p.setPosition(i, j);
        return p;
    }

   void drawDots(sf::RenderWindow& window,vector< sf::CircleShape> pcs) {  
      for(int i =0 ; i < pcs.size();i++)
           window.draw(pcs[i]);      
    }


private:
    vector<sf::CircleShape>vec;
    sf::CircleShape p;
};





