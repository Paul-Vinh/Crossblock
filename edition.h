#ifndef EDITION_H
#define EDITION_H

#include <string>
#include <Imagine/Images.h>
#include <Imagine/Graphics.h>
#include "point.h"
#include "config.h"
#include "jeu.h"
#include "param.h"

using namespace Imagine;
using namespace std;

// Fonctions necessaires a l'edition des niveaux
void edition_case(Image<Color>& I, int i, int j, Config& c);
void sauvegarde(string nomfichier, int nbre, Config& c);

#endif // EDITION_H
