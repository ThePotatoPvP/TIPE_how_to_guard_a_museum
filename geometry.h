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

typedef struct Polygon{
    Point* points;
    Link* links;
    int sides;
} Polygon;

int max(int n, int m);
int min(int n, int m);


int __equal_Points__(Point p1, Point p2);
int __equal_Links__(Link l1, Link l2);

int lineInter(Link l1, Link l2);
int onSegment(Point p, Link l);
int orientation(Point p1, Point p2, Point p3);


double dst_Point(Point a, Point b);
double dst_Point_Link(Point p, Link l);

int isSimplePolygon(Polygon poly);

#endif