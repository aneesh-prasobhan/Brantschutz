#include "math.h"
#include <cmath>

int getDistance(int x1, int y1, int x2, int y2)
{
    // Use the Manhattan distance formula to calculate the distance between two rooms
    return abs(x1 - x2) + abs(y1 - y2);
}