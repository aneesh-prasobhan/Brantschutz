#include "map.h"
#include "SFML\Graphics.hpp"
#include "config.h"


Map::Map(int numFloors, int numRoomsPerFloor, int width, int height)
{
    this->numFloors = numFloors;
    this->numRoomsPerFloor = numRoomsPerFloor;
    rooms = new Room**[numFloors];
    for (int i = 0; i < numFloors; i++)
    {
        rooms[i] = new Room*[numRoomsPerFloor];
        for (int j = 0; j < numRoomsPerFloor; j++)
        {
            rooms[i][j] = new Room(width, height, i);
        }
    }
}

Map::~Map()
{
    for (int i = 0; i < numFloors; i++)
    {
        for (int j = 0; j < numRoomsPerFloor; j++)
        {
            delete rooms[i][j];
        }
        delete[] rooms[i];
    }
    delete[] rooms;
}

void Map::setExit(int floor, int room, std::string direction, int neighborFloor, int neighborRoom)
{
    rooms[floor][room]->setExit(direction, rooms[neighborFloor][neighborRoom]);
}

void Map::setRoomOnFire(int floor, int room)
{
    rooms[floor][room]->setOnFire(true);
}

bool Map::isRoomOnFire(int floor, int room)
{
    return rooms[floor][room]->isOnFire();
}

void Map::findQuickestExit()
{
    // implement flood fill algorithm here
}

void Map::drawMap()
{
    // Create the window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Building Map");

    // Load the font
    sf::Font font;
    font.loadFromFile("sansation.ttf");

    // Initialize the text
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::Black);

    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window
        window.clear();

        // Draw the map
        for (int i = 0; i < numFloors; i++) {
            for (int j = 0; j < numRoomsPerFloor; j++) {
                // Draw the room
                sf::RectangleShape room(sf::Vector2f(ROOM_WIDTH, ROOM_HEIGHT));
                room.setPosition(j * ROOM_WIDTH, i * ROOM_HEIGHT);
                room.setFillColor(sf::Color::White);
                window.draw(room);
                // Draw the exits
                sf::Vector2f position = room.getPosition();
                if (rooms[i][j]->getExit("north")) {
                    sf::RectangleShape exit(sf::Vector2f(ROOM_WIDTH, EXIT_THICKNESS));
                    exit.setPosition(position.x, position.y - EXIT_THICKNESS);
                    exit.setFillColor(sf::Color::Black);
                    window.draw(exit);
                }
                if (rooms[i][j]->getExit("east")) {
                    sf::RectangleShape exit(sf::Vector2f(EXIT_THICKNESS, ROOM_HEIGHT));
                    exit.setPosition(position.x + ROOM_WIDTH, position.y);
                    exit.setFillColor(sf::Color::Black);
                    window.draw(exit);
                }
                if (rooms[i][j]->getExit("south")) {
                    sf::RectangleShape exit(sf::Vector2f(ROOM_WIDTH, EXIT_THICKNESS));
                    exit.setPosition(position.x, position.y + ROOM_HEIGHT);
                    exit.setFillColor(sf::Color::Black);
                    window.draw(exit);
                }
                if (rooms[i][j]->getExit("west")) {
                    sf::RectangleShape exit(sf::Vector2f(EXIT_THICKNESS, ROOM_HEIGHT));
                    exit.setPosition(position.x - EXIT_THICKNESS, position.y);
                    exit.setFillColor(sf::Color::Black);
                    window.draw(exit);
                }

                // Draw the escape route
                if (rooms[i][j]->isOnFire()) {
                    sf::RectangleShape escapeRoute(sf::Vector2f(ROOM_WIDTH, ROOM_HEIGHT));
                    escapeRoute.setPosition(rooms[i][j]->getEscapeX() * ROOM_WIDTH, rooms[i][j]->getEscapeY() * ROOM_HEIGHT);
                    escapeRoute.setFillColor(sf::Color::Green);
                    window.draw(escapeRoute);
                }
            }
        }

        // Draw the text
        text.setString("Floor: " + std::to_string(currentFloor + 1));
        text.setPosition(5, 5);
        window.draw(text);

        // Display the window
        window.display();
    }
}

Room*** Map::getRooms() {
    return rooms;
}

int Map::getEscapeX(int floor, int room) {
    return rooms[floor][room]->getEscapeX();
}
int Map::getEscapeY(int floor, int room) {
    return rooms[floor][room]->getEscapeY();
}
