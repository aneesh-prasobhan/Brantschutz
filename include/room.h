#ifndef ROOM_H
#define ROOM_H

#include <map>
#include <string>

class Room
{
public:
    Room(int width, int height, int floor, int roomNumber = -1);
    void setExit(std::string direction, Room* neighbor);
    void setOnFire(bool onFire);
    bool isOnFire();
    int getFloor();
    int getRoomNumber();
    int getWidth();
    int getHeight();
    int getEscapeX();
    int getEscapeY();

private:
    int width;
    int height;
    int floor;
    int roomNumber;
    bool onFire;
    int escapeX;
    int escapeY;
    std::map<std::string, Room*> exits;
};

#endif
