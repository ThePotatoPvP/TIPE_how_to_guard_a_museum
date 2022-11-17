#ifndef GEOMETRY
#define GEOMETRY

typedef struct Point{
    int x;
    int y;
} Point;

typedef struct Link{
    Point p1;
    Point p2;
} Link;



int croisement(Link* l, int length);

int lineInter(Link l1, Link l2);
int onSegment(Point p, Link l);
int orientation(Point p1, Point p2, Point p3);


double dst_Point(Point a, Point b);

#endif