#include "input.h"

Input::Input()
{
    // Initialize the input
    mouseButtonPressed = false;
    window.create(sf::VideoMode(800, 600), "Map", sf::Style::Titlebar | sf::Style::Close);
}

void Input::update()
{
    // Update the state of the input
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left) {
                mouseButtonPressed = true;
                mouseX = event.mouseButton.x;
                mouseY = event.mouseButton.y;
            }
            break;
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Left) {
                mouseButtonPressed = false;
            }
            break;
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
}

bool Input::isMouseButtonPressed()
{
    return mouseButtonPressed;
}

int Input::getMouseX()
{
    return mouseX;
}

int Input::getMouseY()
{
    return mouseY;
}
