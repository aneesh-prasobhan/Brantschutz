#include "config.h"
#include "input.h"
#include "map.h"
#include "../include/math.h"
#include "output.h"

int main()
{
    // Initialize the map
    Map map;
    map.setCurrentFloor(0);
    map.initialize();

    // Draw the map
    map.drawMap();

    return 0;
}