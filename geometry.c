#include "geometry.h"
#include <math.h>

double dst_Point(Point a, Point b){
    int delta_x = a.x - b.x;
    int delta_y = a.y - b.y;
    return sqrt(delta_x * delta_x + delta_y * delta_y);
}

