#include <stdio.h>
#include <math.h>

#define XMAX 640
#define YMAX 480
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

struct point
{
    int x;
    int y;
};

//  | -------------pt2
//  |               |
//  |               |
// pt1 --------------
struct rect
{
    struct point pt1;
    struct point pt2;
};

struct point makepoint(int x, int y)
{
    struct point temp;
    temp.x = x;
    temp.y = y;
    return temp;
}
// addpoint(makepoint(3,4), makepoint(1,2)) → returns a point with x=4, y=6
struct point addpoint(struct point p1, struct point p2)
{
    p1.x += p2.x;
    p1.y += p2.y;
    return p1;
}
// check whether point p inside rect 
// excludes top and right sides. so p.x == r.pt2.x means the point is exactly on the right edge, which is excluded.
int ptinrect(struct point p, struct rect r)
{
    return p.x >= r.pt1.x && p.x < r.pt2.x // r.pt1.x is x of pt1, which is inside r.
        && p.y >= r.pt1.y && p.y < r.pt2.y;
}

// make sure pt1 is always the bottom-left corner and pt2 is always the top-right corner
struct rect canonrect(struct rect r)
{
    struct rect temp;
    temp.pt1.x = min(r.pt1.x, r.pt2.x);
    temp.pt1.y = min(r.pt1.y, r.pt2.y);
    temp.pt2.x = max(r.pt1.x, r.pt2.x);
    temp.pt2.y = max(r.pt1.y, r.pt2.y);
    return temp;
}

int main()
{
    struct rect screen;
    struct point middle, p;
    struct point origin, *pp; // declare a point and a pointer to point

    screen.pt1 = makepoint(0, 0); 
    screen.pt2 = makepoint(XMAX, YMAX); // top-right at (640, 480)
    middle = makepoint((screen.pt1.x + screen.pt2.x)/2, (screen.pt1.y + screen.pt2.y)/2); // center of screen = (320, 240)

    // print screen info
    printf("screen pt1: (%d,%d)\n", screen.pt1.x, screen.pt1.y);
    printf("screen pt2: (%d,%d)\n", screen.pt2.x, screen.pt2.y);
    printf("middle: (%d,%d)\n", middle.x, middle.y);

    // test ptinrect check point in rect
    p = makepoint(300, 200);
    printf("point (%d,%d) in screen? %d\n", p.x, p.y, ptinrect(p, screen));
    p = makepoint(700, 200);
    printf("point (%d,%d) in screen? %d\n", p.x, p.y, ptinrect(p, screen));

    // test add point
    struct point a = makepoint(3, 4);
    struct point b = makepoint(1, 2);
    struct point sum = addpoint(a, b);
    printf("addpoint: (%d,%d)\n", sum.x, sum.y);

    // test canonrect
    struct rect r;
    r.pt1 = makepoint(100, 200);
    r.pt2 = makepoint(50, 80);
    struct rect cr = canonrect(r);
    printf("canonrect pt1: (%d,%d) pt2: (%d,%d)\n",
        cr.pt1.x, cr.pt1.y, cr.pt2.x, cr.pt2.y);

    // testt pointer to struct
    origin = makepoint(0, 0); // create origin
    pp = &origin; // pp points to origin
    // (*pp).x means x of *pp which is origin () is needed cuz higher precedence than *
    // pp->x shorthand for (*pp).x
    printf("origin via pointer: (%d,%d)\n", (*pp).x, (*pp).y);
    printf("origin via arrow: (%d,%d)\n", pp->x, pp->y);


    // ++p -> len : -> first so p -> len gets len then ++ increase len by 1 
    // len + 1 and p remains
    // (++p) -> len : ++p firsr so moves p to next struct then -> len access len of new struct
    // p move forwards first and read len
    // (p++)->len :  p++ read current p first after that increment
    // *p->str : p->str first so get the str pointer then * so give char str pointing
    // *p->str++ : p->str ( gets str pointer ) first then * read the char then increase after reading
    // *p++->str : p->str first then * get str next increase
    return 0;
}