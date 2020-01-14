#ifndef POINT_H
#define POINT_H
#include <Imagine/Graphics.h>
#include "config.h"
using namespace Imagine;

// initialisation de la structure "Point"
struct Point
{
    int x;
    int y;
};

// Declaration des fonctions de "Point.cpp"
Point operator*(double t, Point p);
Point operator+(Point a, Point b);
bool egal_point(Point a, Point b);

#endif // POINT_H
