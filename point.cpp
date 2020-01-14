#include "point.h"

// Multiplication d'un scalaire avec 1 point
Point operator*(double t, Point p) {
    Point a;
    a.x = t * p.x;
    a.y = t * p.y;
    return(a);
}

// Addition de 2 points
Point operator+(Point a, Point b) {
    Point c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return(c);
}

// Regarde si 2 points sont egaux
bool egal_point(Point a, Point b) {
    if(a.x == b.x && a.y == b.y)
        return(true);
    return(false);
}
