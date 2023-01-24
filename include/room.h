#ifndef ROOM_H
#define ROOM_H

#include <map>

#include <string>
class Room {
public:
	Room(int x, int y);
	void addExit(std::string direction, Room* neighbor);
	void setExit(std::string direction, Room* neighbor);
	void setOnFire(bool onFire);
	bool isOnFire();
	std::map<std::string, Room*> getExits();
	int getX();
	int getY();
	int getEscapeX();
	int getEscapeY();
	void setEscapeX(int x);
	void setEscapeY(int y);

private:
	int x;
	int y;
	std::map<std::string, Room*> exits;
	bool onFire;
	int escapeX;
	int escapeY;
};

#endif