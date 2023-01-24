#ifndef MAP_H
#define MAP_H

#include "room.h"
#include <SFML\Graphics.hpp>
#include "config.h"

class Map {
public:
	Map();
	~Map();
	void initialize();
	void setExit(int floor, int room, std::string direction, int neighborFloor, int neighborRoom);
	void setRoomOnFire(int floor, int room);
	bool isRoomOnFire(int floor, int room);
	void findQuickestExit();
	void drawMap();
	void setCurrentFloor(int floor);
	int getCurrentFloor();
	int Map::getEscapeX(int floor, int room);
	int Map::getEscapeY(int floor, int room);
private:
	int currentFloor;
	Room*** rooms;
	Room*** Map::getRooms();
};





#endif