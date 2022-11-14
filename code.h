#ifndef HEADERFILE
#define HEADERFILE

typedef struct Point{
    int x;
    int y;
} Point;

typedef struct Link{
    Point p1;
    Point p2;
} Link;

typedef struct Node{
    Point p;
    struct Node* next;
} Node;

typedef struct Pile{
    Node* head;
    int depth;
} Pile;

typedef struct Polygon{
    Point* points;
    Link* links;
    int sides;
} Polygon;



// Printers & basics

int max(int n, int m);
int min(int n, int m);

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
int samePoint(Point p1, Point p2);
int getIndex(Point* points, Point p, int n);
int ismem(Pile *pile, Point p);


Point* makePoints(int n);
Link* makeLinks(Point* p,int n);

int croisement(Link* l, int length);

int lineInter(Link l1, Link l2);
int onSegment(Point p, Link l);
int orientation(Point p1, Point p2, Point p3);

// Polygons Funcs

void toFile(Polygon poly, int n);
Polygon* fromFile(void);
int isSimplePolygon(Polygon poly, int n);


#endif

