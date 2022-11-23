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

/**
 * Returns true if the two points have the same coordonates, false otherwise
 * @param p1 a Point
 * @param p2 a Point
 */
int __equal_Points__(Point p1, Point p2);

/**
 * Returns true if the two links share the same points, false otherwise
 * @param l1 a Link
 * @param l2 a Link
 */
int __equal_Links__(Link l1, Link l2);

/**
 * Returns true if two links intersect, false otherwise
 * @param l1 a Link
 * @param l2 a Link
 */
int lineInter(Link l1, Link l2);
int onSegment(Point p, Link l);

/**
 * Returns the spinning way to go from point 1 to 3
 * 0 points are collinear
 * 1 if the rotation is clockwise
 * -1 if anti-clockwise
 * @param p1 a Point
 * @param p2 a Point
 * @param p3 a Point
 */
int orientation(Point p1, Point p2, Point p3);


double dst_Point(Point a, Point b);
double dst_Point_Link(Point p, Link l);

double double_abs(double d);

/**
 * Returns the absolute value of the angle from p2 to p3 taking p1 as origin
 * @param p1 a Point
 * @param p2 a Point
 * @param p3 a Point
 */
double angle_Points(Point p1, Point p2, Point p3);

int isSimplePolygon(Polygon poly);

Point centroid(Point* points, int n);


#endif