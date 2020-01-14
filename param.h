#ifndef PARAM_H
#define PARAM_H

#include <Imagine/Images.h>
using namespace Imagine;
#include <stdio.h>
#include <string>
using namespace std;
#include "config.h"

// Image avec nombre de cases a enlever a la fois
struct Param {
    Image<Color> I;
    int nbre;
};

Param txt_to_image(string nomFichier, Config &c);

#endif // PARAM_H
