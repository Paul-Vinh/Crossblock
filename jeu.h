#ifndef JEU_H
#define JEU_H
#include <string>
#include <Imagine/Images.h>
#include <Imagine/Graphics.h>
#include "point.h"
#include "param.h"
#include "edition.h"
#include "config.h"

using namespace Imagine;
using namespace std;

// Fonctions necessaires au bon fonctionnement du jeu
void affichage(int nbre_blocs, Config c); // affiche le nombre de blocs a casser en meme temps
void coloriage_cases(int compteur, string ligne, Image<Color> I, Config &c); // lecture d'une ligne du fichier texte .txt
vector<Point> selectionLigne(Image<Color> I, int& x1, int& y1, int& x2, int& y2, string nomFichier, Config &c, int niv, bool campagne); // trace la ligne qui coupe les blocs
vector<Point> case_crossed(Point a, Point b, Config &c); // retourne un vecteuir des blocs traverses
bool cross_valid(std::vector<Point> v, int nombre); // renvoie si oui ou non les blocs peuvent etre detruits
void disparition_bloc(Image<Color> I, int x, int y, int l, int h, Config c); // animation de disparition des blocs
void efface_valid(std::vector<Point> v, Image<Color> I, Config &c); // efface les blocs donnes en parametre
bool empty(Config c); // renvoie si oui ou non la map est vide
void play(string nomFichier, Config c, int niv, bool campagne); // joue au niveau donné
void niveauSuivant(int niv, Config& c); // lance le niveau suivant

#endif // JEU_H
