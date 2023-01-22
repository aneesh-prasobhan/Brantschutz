#include "output.h"
#include "map.h"
#include "SFML\Graphics.hpp"
#include "config.h"

Output::Output()
{
    // Create the window
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Building Map");

    // Load the font
    font.loadFromFile("arial.ttf");

    // Initialize the text
    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::Black);
}

void Output::draw(Map& map)
{
    // Clear the window
    window.clear();

    // Draw the map
    for (int i = 0; i < NUM_FLOORS; i++) {
        for (int j = 0; j < NUM_ROOMS_PER_FLOOR; j++) {
            // Draw the room
            sf::RectangleShape room(sf::Vector2f(ROOM_WIDTH, ROOM_HEIGHT));
            room.setPosition(j * ROOM_WIDTH, i * ROOM_HEIGHT);
            room.setFillColor(sf::Color::White);
            window.draw(room);

            // Draw the escape route
            if (map.isRoomOnFire(i, j)) {
                sf::RectangleShape escapeRoute(sf::Vector2f(ROOM_WIDTH, ROOM_HEIGHT));
                escapeRoute.setPosition(map.getEscapeX(i, j) * ROOM_WIDTH, map.getEscapeY(i, j) * ROOM_HEIGHT);
                escapeRoute.setFillColor(sf::Color::Green);
                window.draw(escapeRoute);
            }
        }
    }

    // Draw the text
    text.setString("Escape Route");
    text.setPosition(10, 10);
    window.draw(text);

    // Display the window
    window.display();

}