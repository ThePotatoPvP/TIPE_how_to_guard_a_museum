#include "geometry.h"
#include <math.h>

double dst_Point(Point a, Point b){
    int delta_x = a.x - b.x;
    int delta_y = a.y - b.y;
    return sqrt(delta_x * delta_x + delta_y * delta_y);
}

double dst_Point_Link(Point p, Link l){
    int c = (l.p2.x-l.p1.x);
    int d = (l.p2.y-l.p1.y);
    int dot = (p.x-l.p1.x)*c+(p.y-l.p1.y)*d;
    double var = (double)dot/(double)(c*c+d*d);

    if (var < 0) return dst_Point(l.p1, p);
    if (var > 1) return dst_Point(l.p2, p);

    Point dummy = {(int)(l.p1.x + var*l.p2.x), (int)(l.p1.y + var*l.p2.y)};
    return dst_Point(dummy, p);
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

int onSegment(Point p, Link l){
    return ((p.x >= min(l.p1.x,l.p2.x) && p.x <= max(l.p1.x,l.p2.x))
            && (p.y >= min(l.p1.y,l.p2.y) && p.y <= max(l.p1.y,l.p2.y)));
}

int orientation(Point p1, Point p2, Point p3){
    int val = (p2.y - p1.y)*(p3.x - p2.x)-(p2.x - p1.x)*(p3.y - p2.y);
    if (val == 0){return 0;} // collinéaire
    return (val > 0)? 1: 2;
}

int lineInter(Link l1, Link l2){
    // On a intersection si et seulement si (l1,p2) et (l1.q2) ont une orientation différente
    // aux indices près
    int o1 = orientation(l1.p1,l1.p2,l2.p1);
    int o2 = orientation(l1.p2,l1.p2,l2.p2);
    int o3 = orientation(l2.p1,l2.p2,l1.p1);
    int o4 = orientation(l2.p1,l2.p2,l1.p2);

    if( o1 != o2 && o3 != o4){return 1;}

    // Cas collinéaires où un point est sur l'autre segment
    if (o1 == 0 && onSegment(l2.p1,l1)){return 1;}
    if (o2 == 0 && onSegment(l2.p2,l1)){return 1;}
    if (o3 == 0 && onSegment(l1.p1,l2)){return 1;}
    if (o4 == 0 && onSegment(l1.p2,l2)){return 1;}

    return 0;
}

int isSimplePolygon(Polygon poly){
    int n = poly.sides;
    for(int i=0; i<n; i++){
        for(int j=0; j<i; j++){
            if (lineInter(poly.links[i],poly.links[j])){
                return 0;
            }
        }
    }
    return 1;
}

double double_abs(double d){
    if (d>(double)0){
        return d;
    }
    return (double)(-1)*d;
}

double angle_Points(Point p1, Point p2, Point p3){
    double a_1 = atan((double)(p2.x-p1.x)/(double)(p2.y-p1.y));
    double a_2 = atan((double)(p3.x-p1.x)/(double)(p3.y-p1.y));
    return double_abs(a_2-a_1);
}

Point centroid(Point* points, int n){
    int x, y;
    int length = n;
    for (int i=0; i<length; i++){
        x += points[i].x;
        y += points[i].y;
    }
    return (Point){x/length, y/length};

}