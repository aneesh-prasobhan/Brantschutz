#ifndef INPUT_H
#define INPUT_H

#include "SFML/Graphics.hpp"

class Input
{
public:
	Input();
	void update();
	bool isMouseButtonPressed();
	int getMouseX();
	int getMouseY();

private:
	bool mouseButtonPressed;
	int mouseX;
	int mouseY;
	sf::RenderWindow window;
};

#endif