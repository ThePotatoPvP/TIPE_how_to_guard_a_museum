#include "geometry.h"
#include <math.h>

double dst_Point(Point a, Point b){
    int delta_x = a.x - b.x;
    int delta_y = a.y - b.y;
    return sqrt(delta_x * delta_x + delta_y * delta_y);
}


int __equal_Points__(Point p1, Point p2){
    return (p1.x == p2.x && p1.y == p2.y);
}

int __equal_Links__(Link l1, Link l2){
    return ((__equal_Points__(l1.p1,l2.p1) && __equal_Points__(l1.p2,l2.p2))
    || (__equal_Points__(l1.p1,l2.p2) && __equal_Points__(l1.p2,l2.p1)));
}

int has_common_Point(Link l1, Link l2){
    return (__equal_Points__(l1.p1, l2.p1) ||
            __equal_Points__(l1.p1, l2.p2) ||
            __equal_Points__(l1.p2, l2.p1) ||
            __equal_Points__(l1.p2, l2.p2));
}

Link reversed_Link(Link l){
    return (Link){l.p2, l.p1};
}

int main(){
    return;
}