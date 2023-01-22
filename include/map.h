#ifndef MAP_H
#define MAP_H

#include <string>
#include "room.h"

class Map
{
public:
    Map(int numFloors, int numRoomsPerFloor, int width, int height);
    ~Map();
    void setExit(int floor, int room, std::string direction, int neighborFloor, int neighborRoom);
    void setRoomOnFire(int floor, int room);
    bool isRoomOnFire(int floor, int room);
    void findQuickestExit();
    void drawMap();
        Room*** getRooms();
    int getEscapeX(int floor, int room);
    int getEscapeY(int floor, int room);


private:
    int numFloors;
    int numRoomsPerFloor;
    Room*** rooms;
};

#endif
