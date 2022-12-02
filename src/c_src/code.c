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
            my_XDrawPolygon(d, w, PolygonGC, poly);
            XSetForeground(d, DefaultGC(d,s), 255<<16);
            char* msg;
            Point middle = centroid(poly.points);
            if (isInside(middle,poly)){
                msg = "Centroid is inside";
            } else {
                msg = "Centroid is outside";
            }
            my_XDrawPoint(d, w, DefaultGC(d, s), middle);
            
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

void my_XDrawPoint(Display* d, Window w, GC gc, Point p){
    XFillRectangle(d, w, gc, 
                    MARGE+p.x - POINTWIDTH, 
                    MARGE+p.y - POINTWIDTH, 
                    2*POINTWIDTH, 2*POINTWIDTH
                );
}

void my_XDrawLink(Display* d, Window w, GC gc, Link l){
    XDrawLine(d, w, gc, 
                    MARGE+l.p1.x,
                    MARGE+l.p1.y,
                    MARGE+l.p2.x,
                    MARGE+l.p2.y
                );
}

void my_XDrawPolygon(Display *d, Window w, GC gc, Polygon poly){
    for (int  i=0; i<poly.points->size; i++){
        my_XDrawPoint(d, w, gc, *(Point*)get_LinkedList(poly.points, i));
    }
    for (int i=0; i<poly.links->size; i++){
        my_XDrawLink(d, w, gc, *(Link*)get_LinkedList(poly.links, i));
    }
}

void Polygon_to_file(Polygon* poly, char* filename){
    FILE *fp;
    fp = fopen(filename,"w+");
    int i=0;
    for(Node* node = poly->links->head; i++ < poly->links->size - 1; node = node->next){
        Link* link = node->value;
        char* x = as_str_Rational(int_to_Rational(link->p1.x));
        char* y = as_str_Rational(int_to_Rational(link->p1.y));
        fprintf(fp, "{%s,%s}", x, y);
        free(x);
        free(y);
    }
    fclose(fp);
}

Polygon* file_to_Polygon(char* filename){
    FILE *fp = fopen(filename,"r");
    char buffer[100];

    int i = 0;

    Polygon* polygon = new_Polygon(new_LinkedList(), new_LinkedList());

    while(!feof(fp)){
        char c = fgetc(fp);
        Rational x;
        Rational y;
        if (c == '{'){
            c = fgetc(fp);
            while(c != ','){
                buffer[i++] = c;
                c = fgetc(fp);
            }
            buffer[i++] = '\0';
            x = str_to_Rational(buffer);
            buffer[i] = '0';
            i = 0;
            c = fgetc(fp);
            while(c != '}'){
                buffer[i++] = c;
                c = fgetc(fp);
            }
            buffer[i++] = '\0';
            y = str_to_Rational(buffer);
            buffer[i] = '\0';
            i = 0;
        }
        Point* point = malloc(sizeof(Point));
        point->x = Rational_to_int(x);
        point->y = Rational_to_int(y);

        if(!is_empty_LinkedList(polygon->points)){

            Link* link = malloc(sizeof(Link));
            link->p1 = *(Point*)polygon->points->tail->value;
            link->p2 = *point;

            append_LinkedList(polygon->links, link);
            polygon->sides++;
        }

        append_LinkedList(polygon->points, point);
    }

    if(polygon->points->size >= 2){
        Link* last = malloc(sizeof(Link));
        last->p1 = *(Point*)polygon->points->tail->value;
        last->p2 = *(Point*)polygon->points->head->value;
        append_LinkedList(polygon->links, last);
    }
    return polygon;
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

int main(void) {
    LinkedList* pointsList = makePoints(NPOINTS);
    pointsList = noDubs(pointsList);
    //printPoints(pointsList, NPOINTS);

    //LinkedList* linksList = makeLinks(pointsList);   // try to really make the link
    //Link* linksList = noLinks(pointsList, NPOINTS);   // make dummy links to analyse the dots
    LinkedList* linksList = jarvis(pointsList);
    Polygon* poly = new_Polygon(pointsList, linksList);

    //toFile(pointsList, linksList, NPOINTS);

    //printLinks(pointsList, linksList, NPOINTS);
    //printLinksLetters(pointsList, linksList, NPOINTS);


    //int isSimple = isSimplePolygon(poly);
    makeWindow(*poly);
    return 0;
}

