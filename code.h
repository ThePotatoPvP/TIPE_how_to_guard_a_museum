#ifndef HEADERFILE
#define HEADERFILE
#include "geometry.h"



typedef struct Node{
    Point p;
    struct Node* next;
} Node;

typedef struct Pile{
    Node* head;
    int depth;
} Pile;



// Printers & basics


int isInside(Point p, Polygon poly);
void swap(Point* p, int i, int j);
void sortPoints(Point* p, int n);
char* letterFromInt(int n);

void printPoint(Point p);
void printPoints(Point* p, int n);

void printLinks(Point* p, Link* l, int n);
void printLinkLetter(Point* p, Link* l, int i, int n);
void printLinksLetters(Point* p, Link* l, int n);
void printPile(Pile *pile);
void printPath(Point* p, Link *l, int length);



// Pile funcs



Point depile(Pile *pile);
void empile(Pile *pile, Point p);
Pile* newPile();
int isEmpty(Pile *pile);
void emptyIn(Pile *pil1, Pile *pile2);



// Points & Links



int dubsExist(Point* p, int n);
Point* noDubs(Point* p, int n);
int getIndex(Point* points, Point p, int n);
int ismem(Pile *pile, Point p);


Point* makePoints(int n);
Link* makeLinks(Point* p,int n);

int croisement(Link* l, int length);


// Polygons Funcs

void toFile(Polygon poly, int n);
Polygon* fromFile(void);


#endif

