#include "Screen.h"
#include <iostream>
int main()
{
    Screen* screen = new Screen(16.f / 9.f, 1200);
    while (screen->_window().isOpen())
    {
        sf::Event event;
        while (screen->_window().pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                screen->_window().close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left)
                    if (screen->mouseOnMatrix())
                        screen->setPoint();
                if (event.mouseButton.button == sf::Mouse::Right) {
                    while (event.type != sf::Event::MouseButtonReleased) {
                        if (screen->mouseOnMatrix())
                            screen->setWall();
                        screen->_window().pollEvent(event);
                        screen->draw(sf::Color(192, 200, 209));
                    }
                }
            }
        }
        screen->draw(sf::Color(192, 200, 209));
    }
    return 0;
}