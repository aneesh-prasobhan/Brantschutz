#include "room.h"
#include <string>

Room::Room(int width, int height, int floor, int roomNumber) : roomNumber(roomNumber), escapeX(-1), escapeY(-1)
{
    this->width = width;
    this->height = height;
    this->floor = floor;
    onFire = false;
}

void Room::setExit(std::string direction, Room* neighbor)
{
    exits[direction] = neighbor;
}

void Room::setOnFire(bool onFire)
{
    this->onFire = onFire;
}

bool Room::isOnFire()
{
    return onFire;
}

int Room::getFloor()
{
    return floor;
}

int Room::getRoomNumber()
{
    return roomNumber;
}

int Room::getWidth()
{
    return width;
}

int Room::getHeight()
{
    return height;
}

int Room::getEscapeX()
{
    return escapeX;
}
int Room::getEscapeY()
{
    return escapeY;
}