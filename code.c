#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <X11/Xlib.h>
#include <time.h>
#include "code.h"

#define MARGE 100
#define SIZE 500
#define POINTWIDTH 2
#define NPOINTS 30
//Le 0 0 est en haut à gauche
//xD on est dans Z/nZ


///
// Prints def
///

 

int isInside(Point p, Polygon poly){
    int myBool = 0;
    for(int i=0; i<poly.sides; i++){
        myBool += lineInter(poly.links[i], (Link){p, (Point){2*SIZE,2*SIZE}});
    }
    return myBool%2;
}

void swap(Point* p, int i, int j){
    Point temp = p[j];
    p[j] = p[i];
    p[i] = temp;
}

void sortPoints(Point* p, int n){
    for(int i=n-1; i>0; i--){
        for(int j=0; j<i; j++){
            if (p[j+1].x < p[j].x){swap(p,j,j+1);}
        }
    }
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

void printLinkLetter(Point* p, Link* l,int i, int n){
    printf("Link from (%c) to (%c)\n", letterFromInt(getIndex(p, l[i].p1, n))[0], letterFromInt(getIndex(p, l[i].p2, n))[0]);
}

void printLinksLetters(Point* p, Link* l, int n){
    for(int i=0; i<n; i++){
        printLinkLetter(p,l,i,n);
    }
}

void printPile(Pile *pile){
    Pile *side = newPile();
    printf("Voici la pile :\n");
    while (!(isEmpty(pile))){
        Point newp = depile(pile);
        empile(side, newp);
        printPoint(newp);
    }
    emptyIn(side, pile);
    free(side);
    printf("\n");
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
// Pile functions
///



Point depile(Pile *pile){
    Point p;
    Node *depiled = pile->head;

    if (!(isEmpty(pile))){
        p = depiled->p;
        pile->head = depiled->next;
        free(depiled);
        pile->depth -= 1;
    }
    return p;
}

void empile(Pile *pile, Point p){
    Node *new = malloc(sizeof(Node*));

    new->p = p;
    new->next = pile->head;
    pile->head = new;
    pile->depth += 1;
}

Pile* newPile(){
    Pile *pile = malloc(sizeof(Pile*));
    pile->head = NULL;
    pile->depth = 0;
}

int isEmpty(Pile *pile){
    return (pile->depth == 0);
}

void emptyIn(Pile *pile1, Pile *pile2){
    Point p;
    while (!(isEmpty(pile1))){
        empile(pile2, depile(pile1));
    };
}



///
// Points & links funcs
///



int dubsExist(Point* p, int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<i; j++){
            if(samePoint(p[i],p[j])){return i;}
        }
    }
    return 0;
}

Point* noDubs(Point* p, int n){
    int b = dubsExist(p,n);
    while (b){
        p[b].x = (p[b].x+1) % (SIZE+1);
        b = dubsExist(p,n);
    }
    return p;
}

int samePoint(Point p1, Point p2){
    return (p1.x == p2.x && p1.y == p2.y);
}

int getIndex(Point* points, Point p, int n){
    for(int i=0; i<n; i++){
        if (samePoint(points[i], p)){return i;}
    }
    return -1;
}

int ismem(Pile *pile, Point p){
    Pile *side = newPile();
    while (!(isEmpty(pile))){
        Point newp = depile(pile);
        empile(side, newp);
        if (samePoint(newp, p)){
            emptyIn(side, pile);
            free(side);
            return 1;
        }
    }
    emptyIn(side, pile);
    free(side);
    return 0;
}



Point* makePoints(int n){
    srand(time(NULL));
    Point* p = malloc(sizeof(Point*)*n);
    for(int i=0; i<n; i++){
        p[i].x = rand() % (SIZE+1);
        p[i].y = rand() % (SIZE+1);
    }
    return p;
}

Link* makeLinks(Point* p,int n){
    Link* links = malloc(sizeof(Link)*n);
    sortPoints(p, n);

    Point left = p[0];
    Point right = p[n-1];

    Point* top = malloc(sizeof(Point)*(n-2));
    Point* bottom = malloc(sizeof(Point)*(n-2));
    int bottomi = 0, topi = 0;
    for(int i=1; i<(n-1); i++){
        if (orientation(left, right, p[i]) == 1){
            top[topi++] = p[i];
        }else{
            bottom[bottomi++] = p[i];
        }
    } // On a alors topi + bottomi = n-2
    links[0] = (Link){left, bottom[0]};
    links[1] = (Link){left, top[0]};
    links[2] = (Link){right, top[topi-1]};
    links[3] = (Link){right, bottom[bottomi-1]};

    for(int i=0; i<bottomi; i++){
        links[i+4] = (Link){bottom[i], bottom[i+1]};
    }
    for(int i=0; i<topi-1; i++){
        links[i+3+bottomi] = (Link){top[i], top[i+1]};
    }
    printLinks(p,links, n);
    return links;
}



int croisement(Link* l, int length){
    Link last = l[length-1];
    for(int i=0; i<length-2; i++){
        if (lineInter(last, l[i])){
            return 1;
        };
    };
    return 0;
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

    if( o1 != o2 && o3!= o4){return 1;}

    // Cas collinéaires où un point est sur l'autre segment
    if (o1 == 0 && onSegment(l2.p1,l1)){return 1;}
    if (o2 == 0 && onSegment(l2.p2,l1)){return 1;}
    if (o3 == 0 && onSegment(l1.p1,l2)){return 1;}
    if (o4 == 0 && onSegment(l1.p2,l2)){return 1;}

    return 0;
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

    while (1) {
        XNextEvent(d, &e);
        if (e.type == Expose) {
            for(int i=0; i<n; i++){
                XFillRectangle(d, w, DefaultGC(d, s), 
                    MARGE+poly.points[i].x, 
                    MARGE+poly.points[i].y, 
                    2*POINTWIDTH, 2*POINTWIDTH);

                //char pd[2] = {i+97, '\0'};
                //XDrawString(d, w, DefaultGC(d, s), MARGE+poly.points[i].x + 20, MARGE+poly.points[i].y + 20, pd, 1);
            
                XDrawLine(d, w, DefaultGC(d, s), 
                    MARGE+poly.links[i].p1.x+POINTWIDTH,
                    MARGE+poly.links[i].p1.y+POINTWIDTH,
                    MARGE+poly.links[i].p2.x+POINTWIDTH,
                    MARGE+poly.links[i].p2.y+POINTWIDTH
                );
            };
            if (isInside((Point){250,250}, poly)){
                char* msg = "Center is inside";
                XDrawString(d, w, DefaultGC(d, s), 10, 50, msg, strlen(msg));
            }
            //XDrawString(d, w, DefaultGC(d, s), 10, 50, msg, strlen(msg));
        }
        if (e.type == KeyPress)
            break;
    }

    XCloseDisplay(d);
    free(poly.points);
    free(poly.links);
    return 0;
}



void toFile(Polygon poly, int n){

    FILE *fp;
    char* filename = "polygons.txt";

    fp = fopen(filename,"a+");

    for(int i=0; i<n; i++){
        fprintf(fp, "(%c)[%d, %d] -- ",
            letterFromInt(getIndex(poly.points, poly.links[i].p1, n))[0],
            poly.links[i].p1.x, poly.links[i].p1.y);
        
    }
    fprintf(fp, "(a)[%d, %d]\n", poly.points[0].x, poly.points[0].y);
    fclose(fp);
}

int isSimplePolygon(Polygon poly, int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<i; j++){
            if (lineInter(poly.links[i],poly.links[j])){
                printf("error on link %d\n",i);
                printLinkLetter(poly.points, poly.links,i, n);
                return 0;
            }
        }
        printLinkLetter(poly.points, poly.links,i, n);
        printf("is a clean link");
    }
    return 1;
}

Link* noLinks(Point* p, int n){
    Link* linksList = malloc(sizeof(Link)*n);
    for (int i=0; i<n; i++){ 
        linksList[i].p1 = p[i];
        linksList[i].p2 = p[i];
    }
    return linksList;
}

///
// main()
///



int main(void) {
    Point* pointsList = makePoints(NPOINTS);
    pointsList = noDubs(pointsList, NPOINTS);
    //printPoints(pointsList, NPOINTS);

    Link* linksList = makeLinks(pointsList, NPOINTS);   // try to really make the link
    //Link* linksList = noLinks(pointsList, NPOINTS);   // make dummy links to analyse the dots

    Polygon poly = {pointsList, linksList, NPOINTS};

    //toFile(pointsList, linksList, NPOINTS);

    //printLinks(pointsList, linksList, NPOINTS);
    //printLinksLetters(pointsList, linksList, NPOINTS);


    //int isSimple = isSimplePolygon(poly);

    makeWindow(poly);
    return 0;
}

