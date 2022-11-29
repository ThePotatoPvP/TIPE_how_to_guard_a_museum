#include "geometry.h"
#include "structures.h"
#include <math.h>


Point* new_Point(int x, int y){
    Point* p = malloc(sizeof(p));
    p->x = x;
    p->y = y;
    return p;
}

Link* new_Link(Point p1, Point p2){
    Link *l = malloc(sizeof(Link*));
    l->p1 = p1;
    l->p2=p2;
    return l;
}

Polygon* new_Polygon(LinkedList* points, LinkedList* links){
    Polygon* poly = (Polygon*)malloc(sizeof(poly));
    poly->points = points; 
    poly->links = links;
    poly->sides = links->size;
    return poly;
}

void printPoint(Point p){printf("[%d, %d]", p.x, p.y);}

void printPoints(Point* p, int n){
    for(int i=0; i<n; i++){
        printPoint(p[i]);
        //printf("\n");
    }
}

void printLinks(Point* p, Link* l, int n){
    for(int i=0; i<n; i++){
        printf("Link from [%d,%d] to [%d,%d]\n", 
        l[i].p1.x, l[i].p1.y, l[i].p2.x, l[i].p2.y);
    }
}


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
    int det = (l1.p1.x-l1.p2.x)*(l2.p1.y-l2.p2.y)-(l1.p1.y-l1.p2.y)*(l2.p1.x-l2.p2.x);

    int o1 = orientation(l1.p1,l1.p2,l2.p1);
    int o2 = orientation(l1.p1,l1.p2,l2.p2);
    int o3 = orientation(l2.p1,l2.p2,l1.p1);
    int o4 = orientation(l2.p1,l2.p2,l1.p2);

    if (det != 0 && o1 != o2 && o3 != o4){
        return 1;
    }

    // Cas collinéaires où un point est sur l'autre segment
    if (o1 == 0 && onSegment(l2.p1,l1)){return 1;}
    if (o2 == 0 && onSegment(l2.p2,l1)){return 1;}
    if (o3 == 0 && onSegment(l1.p1,l2)){return 1;}
    if (o4 == 0 && onSegment(l1.p2,l2)){return 1;}

    return 0;

}

/*
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
*/
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

double angle_from_axis(Point p0, Point p1){
    return atan((double)(p1.x-p0.x)/(double)(p1.y-p0.y));
}

Point centroid(LinkedList* points){
    int x=0, y=0;
    for (int i=0; i<points->size; i++){
        Point* p = get_LinkedList(points, i);
        x += p->x;
        y += p->y;
    }
    return (Point){x/(points->size), y/(points->size)};

}

int dumbCalc(Point p1, Point p2, Point p3){

}

LinkedList* jarvis(LinkedList* points){
    LinkedList *hull = new_LinkedList();
    Point* right = get_LinkedList(points, points->size-1);
    Point* cur = right;
    Point* end;
    printf("startofwhile loop\n");
    do{
        append_LinkedList(hull, cur);
        Point* end = get_LinkedList(points, 0);
        for (int j=0; j<points->size; j++){
            Point* pj = get_LinkedList(points, j);
            if ((end == cur) || (orientation(*cur, *end, *pj)==1)){
                end = pj;
            }
        }
        cur = end;
    } while (!(__equal_Points__(*end, *right)));
    printf("done with while loop\n");
    LinkedList* enveloppe = new_LinkedList();
    printf("debut de la boucle for 2\n");
    for (int i=0; i<hull->size; i++){
        printf("building link %i\n",i);
        Link* newLink = new_Link(*(Point*)get_LinkedList(hull, i), 
                                *(Point*)get_LinkedList(hull, (i+1)%(hull->size)));
        append_LinkedList(enveloppe, newLink);
    }
    return enveloppe;
}