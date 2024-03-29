#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <X11/Xlib.h>
#include <time.h>
#include "code.h"
#include "geometry.h"

#define MARGE 100
#define SIZE 500
#define POINTWIDTH 2
#define NPOINTS 10
//Le 0 0 est en haut à gauche
//xD on est dans Z/nZ


///
// Prints def
///



int isInside(Point p, Polygon poly){
    int myBool = 0;
    Point dummy = {2*SIZE, SIZE/2};
    for(int i=0; i<poly.sides; i++){
        if(lineInter(*(Link*)get_LinkedList(poly.links,i), (Link){p, dummy})){
            myBool++;
        }
    }
    return myBool%2;
}

void swap(Point* p, int i, int j){
    Point temp = p[j];
    p[j] = p[i];
    p[i] = temp;
}

int compare_Points(void* p1, void* p2){
    Point* _p1 = (Point*)p1;
    Point* _p2 = (Point*)p2;
    if (_p1->x == _p2->x){return 0;}
    return (_p1->x > _p2->x)? -1: 1;
}

char* letterFromInt(int n){
    unsigned char text = n+'a';
    unsigned char *t = malloc(sizeof(char));
    t[0] = text;
    return t;
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

void printPath(Point* p, Link *l, int length){
    for(int i=0; i<length; i++){
        printPoint(l[i].p1);
        printf(" -- ");
    }
    printPoint(l[length-1].p2);
    printf("\n");
}



int max(int n, int m){return (n>m)? n:m;}
int min(int n, int m){return (n<m)? n:m;}



///
// Points & links funcs
///



int dubsExist(LinkedList* points){
    for(int i=0; i<points->size; i++){
        for(int j=0; j<i; j++){
            if(__equal_Points__(*(Point*)get_LinkedList(points, i),*(Point*)get_LinkedList(points, j))){return i;}
        }
    }
    return 0;
}

LinkedList* noDubs(LinkedList* points){
    int b = dubsExist(points);
    while (b){
        Point* p = get_LinkedList(points, b);
        p->x = (p->x+1) % (SIZE+1);
        b = dubsExist(points);
    }
    return points;
}



LinkedList* makePoints(int n){
    srand(time(NULL));
    LinkedList* points = new_LinkedList();
    for(int i=0; i<n; i++){
        Point* filler = new_Point(rand() % (SIZE+1), rand() % (SIZE+1));
        append_LinkedList(points, filler);
    }
    return points;
}

LinkedList* makeLinks(LinkedList* points){
    LinkedList* links = new_LinkedList();
    sort_LinkedList(points, compare_Points);

    Point* left = get_LinkedList(points, 0);
    Point* right = get_LinkedList(points, points->size-1);

    LinkedList* top = new_LinkedList();
    LinkedList* bottom = new_LinkedList();

    for(int i=1; i<(points->size-1); i++){
        Point* current = get_LinkedList(points, i);
        if (orientation(*left, *right, *current) == 1){
            append_LinkedList(top, current);
        }else{
            append_LinkedList(bottom, current);
        }
    }
    append_LinkedList(links, new_Link(*left, *(Point*)get_LinkedList(bottom, 0)));
    append_LinkedList(links, new_Link(*left, *(Point*)get_LinkedList(top, 0)));
    append_LinkedList(links, new_Link(*right, *(Point*)get_LinkedList(top, top->size-1)));
    append_LinkedList(links, new_Link(*right, *(Point*)get_LinkedList(bottom, bottom->size-1)));
    for(int i=1; i<bottom->size; i++){
        append_LinkedList(links, new_Link(*(Point*)get_LinkedList(bottom,i-1), *(Point*)get_LinkedList(bottom,i)));
    }
    for(int i=1; i<top->size; i++){
        append_LinkedList(links, new_Link(*(Point*)get_LinkedList(top,i-1), *(Point*)get_LinkedList(top,i)));
    }

    return links;
}



int makeWindow(Polygon poly){
    Display *d;
    Window w;
    XEvent e;
    int s;
    int n = poly.sides;

    d = XOpenDisplay(NULL);
    if (d == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, SIZE + 2*MARGE, SIZE+2*MARGE, 1, BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapWindow(d, w);

    XGCValues Polygon_values = {.foreground=BlackPixel(d, s), .background=WhitePixel(d, s)};
    GC PolygonGC = XCreateGC(d, RootWindow(d, s), 0, &Polygon_values);

    while (1) {
        XNextEvent(d, &e);
        if (e.type == Expose && e.xexpose.count==0) {
            for(int i=0; i<n; i++){
                Point p = *(Point*)get_LinkedList(poly.points, i);
                XFillRectangle(d, w, PolygonGC,
                    MARGE+p.x - POINTWIDTH,
                    MARGE+p.y - POINTWIDTH,
                    2*POINTWIDTH, 2*POINTWIDTH
                );

                //char pd[2] = {i+97, '\0'};
                //XDrawString(d, w, DefaultGC(d, s), MARGE+poly.points[i].x + 20, MARGE+poly.points[i].y + 20, pd, 1);
                Link* l = (Link*)get_LinkedList(poly.links, i);
                XDrawLine(d, w, PolygonGC,
                    MARGE+l->p1.x,
                    MARGE+l->p1.y,
                    MARGE+l->p2.x,
                    MARGE+l->p2.y
                );
            };
            XSetForeground(d, DefaultGC(d,s), 255<<16);
            XFillRectangle(d, w, DefaultGC(d,s), MARGE+SIZE/2-POINTWIDTH, MARGE+SIZE/2-POINTWIDTH, 2*POINTWIDTH,2*POINTWIDTH);
            char* msg;
            Point middle = {250,250};
            if (isInside(middle,poly)){
                msg = "Center is inside";
            } else {
                msg = "Center is outside";
            }
            XDrawString(d, w, DefaultGC(d, s), MARGE+SIZE/3, MARGE*1.2+SIZE, msg, strlen(msg));
        }
        if (e.type == KeyPress)
            break;
    }

    XCloseDisplay(d);
    free(poly.points);
    free(poly.links);
    return 0;
}



void toFile(Polygon poly){

    FILE *fp;
    char* filename = "polygons.txt";

    fp = fopen(filename,"a+");

    for(int i=0; i<poly.sides; i++){
        Link cur = *(Link*)get_LinkedList(poly.links, i);
        fprintf(fp, "[%d, %d] -- ",
            cur.p1.x, cur.p1.y);

    }
    Point start = *(Point*)get_LinkedList(poly.points, 0);
    fprintf(fp, "[%d, %d]\n", start.x, start.y);
    fclose(fp);
}

LinkedList* noLinks(LinkedList* points){
    LinkedList* links = new_LinkedList();
    for (int i=0; i<points->size; i++){
        Point* point = (Point*)get_LinkedList(points, i);
        Link* link = new_Link(*point, *point);
        append_LinkedList(links, link);
    }
    return links;
}


///
// main()
///

Polygon* createExample1() {
    Point pointList[4] = {
        {0, 0},
        {0, 100},
        {200, 100},
        {200, 0}
    };

    Polygon* rectangle = createPolygon(pointList, 4);

    return rectangle;
}

Polygon* createExample2() {
    Point pointList[] = {
        {100, 100}, {200, 100}, {200, 200}, {300, 200}, {300, 300}, {200, 300},
        {200, 400}, {300, 400}, {300, 500}, {200, 500}, {200, 600}, {100, 600}
    };
    return createPolygon(pointList, 12);
}

Polygon* createExample3() {
    Point pointList[] = {
        {22, 340},{76, 24},{92, 64},{149, 38},{327, 0},
        {376, 22},{485, 41},{484, 85},{394, 92},{373, 36},
        {167, 59},{125, 81},{225, 109},{259, 136},{167, 266},
        {84, 324},{112, 318},{321, 127},{461, 199},{498, 252},
        {354, 181},{301, 198},{291, 217},{337, 285},{461, 364},
        {415, 233},{454, 260},{500, 330},{409, 446},{327, 396},
        {307, 383},{254, 329},{243, 249},{190, 354},{139, 432},
        {266, 500},{116, 481},{16, 494},{16, 387},{0, 227}
    };
    return createPolygon(pointList, 40);
}

Polygon* createExample4() {
    Point pointList[] = {
        {88, 494},{146, 413},{33, 487},{61, 361},{15, 263},
        {0, 218},{53, 66},{43, 12},{166, 0},{433, 41},
        {336, 57},{177, 44},{160, 44},{88, 43},{87, 139},
        {39, 217},{52, 210},{184, 242},{233, 212},{272, 182},
        {314, 143},{121, 218},{106, 162},{259, 157},{287, 131},
        {443, 106},{434, 139},{423, 170},{279, 338},{197, 364},
        {340, 370},{413, 339},{448, 464},{461, 299},{461, 270},
        {500, 194},{478, 302},{477, 500},{392, 433},{203, 434}
    };
    return createPolygon(pointList, 40);
}

Polygon* createExample5() {
    Point pointList[] = {
        {190, 177},{142, 247},{40, 63},{143, 29},{396, 0},
        {291, 113},{494, 63},{492, 86},{477, 220},{481, 325},
        {455, 445},{500, 496},{203, 500},{365, 433},{400, 418},
        {412, 364},{472, 346},{467, 291},{403, 301},{421, 255},
        {316, 321},{267, 415},{382, 419},{285, 441},{100, 442},
        {5, 415},{0, 393},{99, 394},{102, 332},{221, 270},
        {320, 236},{296, 285},{373, 257},{345, 257},{398, 208},
        {475, 125},{343, 176},{280, 196},{189, 254},{112, 297}
    };
    return createPolygon(pointList, 40);
}

int main(void) {
    //LinkedList* pointsList = makePoints(NPOINTS);
    //pointsList = noDubs(pointsList);
    //printPoints(pointsList, NPOINTS);

    //LinkedList* linksList = makeLinks(pointsList);   // try to really make the link
    //Link* linksList = noLinks(pointsList, NPOINTS);   // make dummy links to analyse the dots
    //Polygon* poly = new_Polygon(pointsList, linksList);
    Polygon* poly = createExample4();

    //toFile(pointsList, linksList, NPOINTS);

    //printLinks(pointsList, linksList, NPOINTS);
    //printLinksLetters(pointsList, linksList, NPOINTS);


    //int isSimple = isSimplePolygon(poly);
    makeWindow(*poly);
    return 0;
}

