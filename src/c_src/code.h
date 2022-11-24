#ifndef HEADERFILE
#define HEADERFILE
#include "geometry.h"


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
void printPath(Point* p, Link *l, int length);



// Points & Links



int dubsExist(LinkedList* points);
LinkedList* noDubs(LinkedList* points);
int getIndex(Point* points, Point p, int n);


LinkedList* makePoints(int n);
LinkedList* makeLinks(LinkedList* points);

int croisement(Link* l, int length);


// Polygons Funcs

void toFile(Polygon poly, int n);
Polygon* fromFile(void);


#endif

