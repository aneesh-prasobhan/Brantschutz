#include "room.h"

Room::Room(int x, int y) : escapeX(-1), escapeY(-1)
{
    this->x = x;
    this->y = y;
    onFire = false;
}

void Room::addExit(std::string direction, Room* neighbor)
{
    exits[direction] = neighbor;
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

std::map<std::string, Room*> Room::getExits()
{
    return exits;
}

int Room::getEscapeX() {
    return escapeX;
}
int Room::getEscapeY() {
    return escapeY;
}