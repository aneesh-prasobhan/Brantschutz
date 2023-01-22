#include "map.h"

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
    // implement SFML code to draw the map here
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