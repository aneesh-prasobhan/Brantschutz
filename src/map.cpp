#include "map.h"
#include "SFML\Graphics.hpp"
#include "config.h"


Map::Map() {
    currentFloor = 0;
    rooms = new Room * *[NUM_FLOORS];
    for (int i = 0; i < NUM_FLOORS; i++) {
        rooms[i] = new Room * [NUM_ROOMS_PER_FLOOR];
    }
}


void Map::initialize()
{
    // Initialize the rooms on the first floor
    rooms = new Room * *[NUM_FLOORS];
    for (int i = 0; i < NUM_FLOORS; i++) {
        rooms[i] = new Room * [NUM_ROOMS_PER_FLOOR];
        for (int j = 0; j < NUM_ROOMS_PER_FLOOR; j++) {
            rooms[i][j] = new Room(i, j * NUM_ROOMS_PER_FLOOR + j);
        }
    }
    // Create the exits for the rooms on the first floor
    for (int i = 0; i < NUM_FLOORS; i++) {
        for (int j = 0; j < NUM_ROOMS_PER_FLOOR; j++) {
            // North
            if (i > 0) {
                rooms[i][j]->addExit("north", rooms[i - 1][j]);
            }
            // South
            if (i < NUM_ROOMS_PER_FLOOR - 1) {
                rooms[i][j]->addExit("south", rooms[i + 1][j]);
            }

            // West
            if (j > 0) {
                rooms[i][j]->addExit("west", rooms[i][j - 1]);
            }

            // East
            if (j < NUM_ROOMS_PER_FLOOR - 1) {
                rooms[i][j]->addExit("east", rooms[i][j + 1]);
            }
        }
    }
}


Map::~Map()
{
    for (int i = 0; i < NUM_FLOORS; i++)
    {
        for (int j = 0; j < NUM_ROOMS_PER_FLOOR; j++)
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
    text.setCharacterSize(12);
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
        for (int i = 0; i < NUM_FLOORS; i++) {
            for (int j = 0; j < NUM_ROOMS_PER_FLOOR; j++) {
                // Draw the room
                sf::RectangleShape room(sf::Vector2f(ROOM_WIDTH, ROOM_HEIGHT));
                room.setPosition(j * ROOM_WIDTH, i * ROOM_HEIGHT);
                room.setFillColor(sf::Color::White);
                window.draw(room);

                // Draw the exits
                std::map<std::string, Room*> exits = rooms[i][j]->getExits();
                for (std::map<std::string, Room*>::iterator it = exits.begin(); it != exits.end(); ++it) {
                    sf::RectangleShape exit(sf::Vector2f(EXIT_THICKNESS, ROOM_HEIGHT));
                    if (it->first == "north") {
                        exit.setPosition(j * ROOM_WIDTH, i * ROOM_HEIGHT - EXIT_THICKNESS);
                    }
                    else if (it->first == "south") {
                        exit.setPosition(j * ROOM_WIDTH, (i + 1) * ROOM_HEIGHT);
                    }
                    else if (it->first == "west") {
                        exit.setPosition(j * ROOM_WIDTH - EXIT_THICKNESS, i * ROOM_HEIGHT);
                        exit.setSize(sf::Vector2f(EXIT_THICKNESS, ROOM_WIDTH));
                        exit.setRotation(90);
                    }
                    else if (it->first == "east") {
                        exit.setPosition((j + 1) * ROOM_WIDTH, i * ROOM_HEIGHT);
                        exit.setSize(sf::Vector2f(EXIT_THICKNESS, ROOM_WIDTH));
                        exit.setRotation(90);
                    }
                    window.draw(exit);
                }
                if (rooms[i][j]->isOnFire()) {
                    sf::RectangleShape fire(sf::Vector2f(ROOM_WIDTH, ROOM_HEIGHT));
                    fire.setPosition(j * ROOM_WIDTH, i * ROOM_HEIGHT);
                    fire.setFillColor(sf::Color::Red);
                    window.draw(fire);
                }
                // Draw the sign board with the shortest exit path
                if (rooms[i][j]->getEscapeX() != -1 && rooms[i][j]->getEscapeY() != -1) {
                    sf::RectangleShape signBoard(sf::Vector2f(SIGN_BOARD_WIDTH, SIGN_BOARD_HEIGHT));
                    signBoard.setPosition(j * ROOM_WIDTH + (ROOM_WIDTH - SIGN_BOARD_WIDTH) / 2, i * ROOM_HEIGHT + (ROOM_HEIGHT - SIGN_BOARD_HEIGHT) / 2);
                    signBoard.setFillColor(sf::Color::White);
                    window.draw(signBoard);

                    // Draw the sign board with the shortest exit path
                    if (rooms[i][j]->getEscapeX() != -1 && rooms[i][j]->getEscapeY() != -1) {
                        sf::RectangleShape signBoard(sf::Vector2f(SIGN_BOARD_WIDTH, SIGN_BOARD_HEIGHT));
                        signBoard.setPosition(j * ROOM_WIDTH + (ROOM_WIDTH - SIGN_BOARD_WIDTH) / 2, i * ROOM_HEIGHT + (ROOM_HEIGHT - SIGN_BOARD_HEIGHT) / 2);
                        signBoard.setFillColor(sf::Color::White);
                        window.draw(signBoard);

                        // Draw the arrow on the sign board
                        sf::ConvexShape arrow;
                        arrow.setPointCount(3);
                        arrow.setPoint(0, sf::Vector2f(0, 0));
                        arrow.setPoint(1, sf::Vector2f(SIGN_BOARD_WIDTH / 2, SIGN_BOARD_HEIGHT / 2));
                        arrow.setPoint(2, sf::Vector2f(0, SIGN_BOARD_HEIGHT));
                        arrow.setPosition(j * ROOM_WIDTH + (ROOM_WIDTH - SIGN_BOARD_WIDTH) / 2, i * ROOM_HEIGHT + (ROOM_HEIGHT - SIGN_BOARD_HEIGHT) / 2);

                        // Rotate the arrow based on the escape direction
                        text.setString(std::to_string(rooms[i][j]->getEscapeX()) + "," + std::to_string(rooms[i][j]->getEscapeY()));
                        text.setPosition(j * ROOM_WIDTH + (ROOM_WIDTH - text.getLocalBounds().width) / 2, i * ROOM_HEIGHT + (ROOM_HEIGHT - text.getLocalBounds().height) / 2);
                        window.draw(text);
                    }
                }
            }
        }
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


int Map::getCurrentFloor() {
    return currentFloor;
}

void Map::setCurrentFloor(int floor) {
    currentFloor = floor;
}
