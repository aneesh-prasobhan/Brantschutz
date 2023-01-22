#ifndef OUTPUT_H
#define OUTPUT_H

#include "SFML/Graphics.hpp"
#include "SFML/Window/ContextSettings.hpp"
#include "map.h"
class Output {
    sf::RenderWindow window;
    sf::Font font;
    sf::Text text;

public:
    Output();
    void draw(Map &map);
};

#endif
