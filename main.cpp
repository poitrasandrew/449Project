#include <SFML/Graphics.hpp>
#include "boarb.h"
#include<vector>
int main()
{
    sf::RenderWindow window(sf::VideoMode(720, 720), "9 Men's Morris");
    //board myBoard("main.png");// set the size of the window (550,550) 
    board myBoard(sf::Vector2f(620.f,620.f) ,50.f,50.f);
    board myBoard_1(sf::Vector2f(410.f, 410.f), 155.f, 155.f);
    board myBoard_2(sf::Vector2f(200.f, 200.f), 260.f, 260.f);
 
    std::vector<board> boardVec;
    boardVec.push_back(myBoard);
    boardVec.push_back(myBoard_1);
    boardVec.push_back(myBoard_2);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            //end loop when window closes
            if (event.type == sf::Event::Closed)
                window.close();

        }
        window.clear();
        myBoard.drawPlayer(window);
        myBoard_1.drawPlayer(window);
        myBoard_2.drawPlayer(window);
        window.display();
    }
    
  
   
    return 0;
}