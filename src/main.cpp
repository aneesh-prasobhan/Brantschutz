#include "config.h"
#include "input.h"
#include "map.h"
#include "../include/math.h"
#include "output.h"

int main()
{
    Map* map = new Map(NUM_FLOORS, NUM_ROOMS_PER_FLOOR, ROOM_WIDTH, ROOM_HEIGHT);

    //set exits between rooms
    //example: map->setExit(0, 0, "north", 1, 0);

    //set rooms on fire
    //example: map->setRoomOnFire(2, 3);

    //find quickest exit
    map->findQuickestExit();

    //draw map on screen using SFML
    map->drawMap();

    //clean up memory
    delete map;

    return 0;
}