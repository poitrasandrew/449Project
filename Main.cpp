#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(720, 720), "9 Men's Morris");

    window.setFramerateLimit(60);

    sf::RectangleShape outerSquare(sf::Vector2f(620.f, 620.f));
    outerSquare.setFillColor(sf::Color::Transparent);
    outerSquare.setOutlineThickness(10.f);
    outerSquare.setOutlineColor(sf::Color::Yellow);
    outerSquare.setPosition(sf::Vector2f(50.f, 50.f));

    sf::RectangleShape middleSquare(sf::Vector2f(410.f, 410.f));
    middleSquare.setFillColor(sf::Color::Transparent);
    middleSquare.setOutlineThickness(10.f);
    middleSquare.setOutlineColor(sf::Color::Yellow);
    middleSquare.setPosition(sf::Vector2f(155.f, 155.f));

    sf::RectangleShape innerSquare(sf::Vector2f(200.f, 200.f));
    innerSquare.setFillColor(sf::Color::Transparent);
    innerSquare.setOutlineThickness(10.f);
    innerSquare.setOutlineColor(sf::Color::Yellow);
    innerSquare.setPosition(sf::Vector2f(260.f, 260.f));

    sf::RectangleShape lineTop(sf::Vector2f(210.f, 10.f));
    lineTop.setPosition(sf::Vector2f(365.f, 50.f));
    lineTop.setFillColor(sf::Color::Yellow);
    lineTop.rotate(90.f);

    sf::RectangleShape lineBottom(sf::Vector2f(210.f, 10.f));
    lineBottom.setPosition(sf::Vector2f(365.f, 470.f));
    lineBottom.setFillColor(sf::Color::Yellow);
    lineBottom.rotate(90.f);

    sf::RectangleShape lineLeft(sf::Vector2f(210.f, 10.f));
    lineLeft.setPosition(sf::Vector2f(50.f, 350.f));
    lineLeft.setFillColor(sf::Color::Yellow);

    sf::RectangleShape lineRight(sf::Vector2f(210.f, 10.f));
    lineRight.setPosition(sf::Vector2f(470.f, 350.f));
    lineRight.setFillColor(sf::Color::Yellow);

    //top middle three dots
    sf::CircleShape spot1(15.f);
    spot1.setPosition(sf::Vector2f(345.f, 30.f));
    spot1.setFillColor(sf::Color::Yellow);
    
    sf::CircleShape spot2(15.f);
    spot2.setPosition(sf::Vector2f(345.f, 135.f));
    spot2.setFillColor(sf::Color::Yellow);

    sf::CircleShape spot3(15.f);
    spot3.setPosition(sf::Vector2f(345.f, 240.f));
    spot3.setFillColor(sf::Color::Yellow);

    //bottom middle three dots
    sf::CircleShape spot4(15.f);
    spot4.setPosition(sf::Vector2f(345.f, 450.f));
    spot4.setFillColor(sf::Color::Yellow);

    sf::CircleShape spot5(15.f);
    spot5.setPosition(sf::Vector2f(345.f, 555.f));
    spot5.setFillColor(sf::Color::Yellow);

    sf::CircleShape spot6(15.f);
    spot6.setPosition(sf::Vector2f(345.f, 660.f));
    spot6.setFillColor(sf::Color::Yellow);

    //left outer three dots
    sf::CircleShape spot7(15.f);
    spot7.setPosition(sf::Vector2f(30.f, 30.f));
    spot7.setFillColor(sf::Color::Yellow);

    sf::CircleShape spot8(15.f);
    spot8.setPosition(sf::Vector2f(30.f, 340.f));
    spot8.setFillColor(sf::Color::Yellow);

    sf::CircleShape spot9(15.f);
    spot9.setPosition(sf::Vector2f(30.f, 660.f));
    spot9.setFillColor(sf::Color::Yellow);

    //right outer three dots
    sf::CircleShape spot10(15.f);
    spot10.setPosition(sf::Vector2f(660.f, 30.f));
    spot10.setFillColor(sf::Color::Yellow);

    sf::CircleShape spot11(15.f);
    spot11.setPosition(sf::Vector2f(660.f, 340.f));
    spot11.setFillColor(sf::Color::Yellow);

    sf::CircleShape spot12(15.f);
    spot12.setPosition(sf::Vector2f(660.f, 660.f));
    spot12.setFillColor(sf::Color::Yellow);

    //left middle three dots
    sf::CircleShape spot13(15.f);
    spot13.setPosition(sf::Vector2f(135.f, 135.f));
    spot13.setFillColor(sf::Color::Yellow);

    sf::CircleShape spot14(15.f);
    spot14.setPosition(sf::Vector2f(135.f, 340.f));
    spot14.setFillColor(sf::Color::Yellow);

    sf::CircleShape spot15(15.f);
    spot15.setPosition(sf::Vector2f(135.f, 555.f));
    spot15.setFillColor(sf::Color::Yellow);

    //right middle three dots
    sf::CircleShape spot16(15.f);
    spot16.setPosition(sf::Vector2f(555.f, 135.f));
    spot16.setFillColor(sf::Color::Yellow);

    sf::CircleShape spot17(15.f);
    spot17.setPosition(sf::Vector2f(555.f, 340.f));
    spot17.setFillColor(sf::Color::Yellow);

    sf::CircleShape spot18(15.f);
    spot18.setPosition(sf::Vector2f(555.f, 555.f));
    spot18.setFillColor(sf::Color::Yellow);

    //left inner three dots
    sf::CircleShape spot19(15.f);
    spot19.setPosition(sf::Vector2f(240.f, 240.f));
    spot19.setFillColor(sf::Color::Yellow);

    sf::CircleShape spot20(15.f);
    spot20.setPosition(sf::Vector2f(240.f, 340.f));
    spot20.setFillColor(sf::Color::Yellow);

    sf::CircleShape spot21(15.f);
    spot21.setPosition(sf::Vector2f(240.f, 450.f));
    spot21.setFillColor(sf::Color::Yellow);

    //right inner three dots
    sf::CircleShape spot22(15.f);
    spot22.setPosition(sf::Vector2f(450.f, 240.f));
    spot22.setFillColor(sf::Color::Yellow);

    sf::CircleShape spot23(15.f);
    spot23.setPosition(sf::Vector2f(450.f, 340.f));
    spot23.setFillColor(sf::Color::Yellow);

    sf::CircleShape spot24(15.f);
    spot24.setPosition(sf::Vector2f(450.f, 450.f));
    spot24.setFillColor(sf::Color::Yellow);

    sf::CircleShape white1(20.f);
    white1.setFillColor(sf::Color::White);
    white1.setPosition(sf::Vector2f(360.f, 360.f));

    //put in grid coordinates on the sides of the board a-g on left (y-axis) 1-7 on bottom (x-axis)
    //sf::Text a;
    //a.setString("A");
   // a.setPosition(sf::Vector2f(5.f, 660.f));

    bool selected = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            //end loop when window closes
            if (event.type == sf::Event::Closed)
                window.close(); 
            //chnages origin of the moved dot to make dragging more intuitive on left click and releases dot when left click is released
            else if (sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (white1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        white1.setOrigin(event.mouseButton.x - (white1.getPosition().x - white1.getOrigin().x),
                            event.mouseButton.y - (white1.getPosition().y - white1.getOrigin().y));
                        selected = !selected;
                    }
                }
            }
            //moves the dot around when one has been selected
            if (selected) {
                white1.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            }
        }

        window.clear();
        window.draw(outerSquare);
        window.draw(middleSquare);
        window.draw(innerSquare);
        window.draw(lineTop);
        window.draw(lineBottom);
        window.draw(lineLeft);
        window.draw(lineRight);
        window.draw(spot1);
        window.draw(spot2);
        window.draw(spot3);
        window.draw(spot4);
        window.draw(spot5);
        window.draw(spot6);
        window.draw(spot7);
        window.draw(spot8);
        window.draw(spot9);
        window.draw(spot10);
        window.draw(spot11);
        window.draw(spot12);
        window.draw(spot13);
        window.draw(spot14);
        window.draw(spot15);
        window.draw(spot16);
        window.draw(spot17);
        window.draw(spot18);
        window.draw(spot19);
        window.draw(spot20);
        window.draw(spot21);
        window.draw(spot22);
        window.draw(spot23);
        window.draw(spot24);
        window.draw(white1);
        //window.draw(a);
        window.display();
    }

    return 0;
}