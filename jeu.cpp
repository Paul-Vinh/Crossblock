#include "jeu.h"
#include <Imagine/Images.h>

using namespace std;
using namespace Imagine;

void affichage(int nbre_blocs, Config c) {
    int largeur = c.get_Largeur();
    int hauteur = c.get_Hauteur();

    // image nombre blocs a casser en meme temps
    byte* R = new byte[largeur*hauteur];
    byte* G = new byte[largeur*hauteur];
    byte* B = new byte[largeur*hauteur];

    int w_nb = 120; int h_nb = 50; // dimensions de l'image

    if(nbre_blocs == 2) {
        loadColorImage(srcPath("blocs_2.png"),R,G,B,w_nb,h_nb);
        putColorImage(largeur-120,0,R,G,B,w_nb,h_nb);
    }
    else if(nbre_blocs == 3) {
        loadColorImage(srcPath("blocs_3.png"),R,G,B,w_nb,h_nb);
        putColorImage(largeur-120,0,R,G,B,w_nb,h_nb);
    }
}

void coloriage_cases(int compteur, string ligne, Image<Color> I, Config& c) {
    int largeur = c.get_Largeur();
    int hauteur = c.get_Hauteur();
    int N = c.get_N();

    ligne.erase(std::remove(ligne.begin(), ligne.end(), ' '), ligne.end()); // efface les espaces sur la ligne
    for(int i=0; i<ligne.length(); i++) {
        int x = largeur*i/N; // abscisse a partir des numéros de cases
        int y = hauteur*compteur/N; // ordonnee a partir des numéros de cases

        if(ligne[i] == '1') { // lecture de cases bleues
            for(int k = (largeur*i)/N; k<(largeur*i)/N + largeur/N - 4; k++) {
                for(int l = (hauteur*compteur)/N; l<(hauteur*compteur)/N + hauteur/N - 4; l++) {
                    I(k,l) = BLUE;
                }
            }
            fillRect(x,y,largeur/N-5,hauteur/N-5,BLUE);
            c.set_elem_cas(i,compteur,1);
        }
        else { // lecture de cases blanches
            for(int k = (largeur*i)/N; k<(largeur*i)/N + largeur/N - 4; k++) {
                for(int l = (hauteur*compteur)/N; l<(hauteur*compteur)/N + hauteur/N - 4; l++) {
                    I(k,l) = WHITE;
                }
            }
            fillRect(x,y,largeur/N-5,hauteur/N-5,WHITE);
            c.set_elem_cas(i,compteur,0);
        }
     }
}

vector<Point> selectionLigne(Image<Color> I, int& x1, int& y1, int& x2, int& y2, string nomFichier, Config& c, int niv, bool campagne) { // Selection d'une ligne - trace
    Event e;
    do {
        getEvent(0, e);
        if(e.type==EVT_BUT_ON) { // premier point de la ligne
            x1 = x2 = e.pix[0];
            y1 = y2 = e.pix[1];
        }
        if(e.type==EVT_MOTION) { // tous les points suivants (lorsque la souris bouge)
            x2 = e.pix[0];
            y2 = e.pix[1];
            display(I);
            drawLine(x1,y1,x2,y2,RED,2);
        }
        if(e.type==EVT_KEY_ON) { // si appui sur "R" --> rejouer le niveau
            if(e.key == 'r') {
                play(nomFichier, c, niv, campagne);
            }
        }
    } while(e.type!=EVT_BUT_OFF);
    display(I);
    Point a,b;
    a.x = x1; a.y = y1;
    b.x = x2; b.y = y2;
    vector<Point> v;
    v.push_back(a);
    v.push_back(b);
    return(v);
}

vector<Point> case_crossed(Point a, Point b, Config& c) {
    int largeur = c.get_Largeur();
    int hauteur = c.get_Hauteur();
    int N = c.get_N();

    vector<Point> v;
    int i = a.x * N  / largeur;
    int j = a.y * N  / hauteur;

    Point k;
    k.x = i; k.y = j;
    if(c.get_elem_cas(i,j) == 1)
        v.push_back(k);
    double t = 0.0;
    while(t<1) {
        Point courant = t*b + (1-t)*a;
        int i = courant.x * N / largeur;
        int j = courant.y * N / hauteur;
        Point l;
        l.x = i; l.y = j;
        if(egal_point(l,k) == false && c.get_elem_cas(i,j) == 1) {
            v.push_back(l);
            k = l;
        }
        t = t + 0.05;
    }
    return(v);
}

bool cross_valid(std::vector<Point> v, int nombre) {
    if(v.size() == nombre) {
        Point a = v.back();
        v.pop_back(); // dépilement

        Point b = v.back();
        v.pop_back(); // dépilement

        if(a.x != b.x && a.y != b.y) // si les 2 cases sont les memes
            return(false);

        while(!v.empty()) {
            if(a.x == b.x) {
                Point c = v.back();
                v.pop_back();
                if(c.x != a.x)
                    return(false);
            }
            else if(a.y == b.y) {
                Point c = v.back();
                v.pop_back();
                if(c.y != a.y)
                    return(false);
            }
        }
        return(true);
    }
    return(false);
}

// Animation disparition des blocs
void disparition_bloc(Image<Color> I, int x, int y, int l, int h, Config c) {
    int largeur = c.get_Largeur();
    int hauteur = c.get_Hauteur();

    int fact = 0;
    while(fact < 20){
        fillRect(x+fact,y+fact,l-2*fact,h-2*fact,BLUE); // rétrécissement
        milliSleep(10);
        fillRect(0,0,largeur,hauteur,WHITE); // carre blanc (disparition)
        display(I);
        fact++;
    }
    fillRect(0,0,largeur,hauteur,WHITE);
    display(I);
}

void efface_valid(std::vector<Point> v, Image<Color> I, Config& c) {
    int largeur = c.get_Largeur();
    int hauteur = c.get_Hauteur();
    int N = c.get_N();

    for(int a=0; a<v.size(); a++) {
        Point p = v[a];
        int i = p.x;
        int j = p.y;

        for(int k = (largeur*i)/N; k<(largeur*i)/N + largeur/N - 4; k++) {
            for(int l = (hauteur*j)/N; l<(hauteur*j)/N + hauteur/N - 4; l++) {
                I(k,l) = WHITE;
            }
        }
        c.set_elem_cas(i,j,0);
        int x = largeur*i / N; // abscisse a partir des numéros de cases
        int y = hauteur*j / N; // ordonnee a partir des numéros de cases
        disparition_bloc(I,x,y,largeur/N-5,hauteur/N-5,c);
    }
}

bool empty(Config c) { // fonction qui retourne "oui" si la map est vide (remplie de "0")
    int N = c.get_N();

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            if(c.get_elem_cas(i,j) == 1) // si case non vide
                return(false);
        }
    }
    return(true);
}

void play(string nomFichier, Config c, int niv, bool campagne) { // lance le niveau donné en paramètre
    int largeur = c.get_Largeur();
    int hauteur = c.get_Hauteur();

    Param P = txt_to_image(nomFichier,c);
    Image<Color> I = P.I;
    int x1, y1, x2, y2;
    vector<Point> v;
    int nb = P.nbre;
    affichage(nb, c);
    while(!empty(c)) { // tant que la map n'est pas finie
        v = selectionLigne(I,x1,y1,x2,y2,nomFichier,c,niv,campagne);
        Point a = v[0];
        Point b = v[1];
        vector<Point> cross = case_crossed(a,b,c);
        if(cross_valid(cross, nb)) {
            efface_valid(cross,I,c);
        }
    }
    fillRect(0,0,largeur,hauteur,WHITE);
    if(campagne) // lance le niveau suivant de la campagne
        niveauSuivant(niv+1,c);

    else { // si le joueur a joue au niveau qu'il a édité (pas de niveau suivant = il ne joue pas a la campagne)
        byte* R = new byte[largeur*hauteur];
        byte* G = new byte[largeur*hauteur];
        byte* B = new byte[largeur*hauteur];

        loadColorImage(srcPath("fin.png"),R,G,B,largeur,hauteur); // image de fin
        putColorImage(0,0,R,G,B,largeur,hauteur);
        endGraphics();
    }
}

void niveauSuivant(int niv, Config& c) { // lance le niveau suivant
    int largeur = c.get_Largeur();
    int hauteur = c.get_Hauteur();

    byte* R = new byte[largeur*hauteur];
    byte* G = new byte[largeur*hauteur];
    byte* B = new byte[largeur*hauteur];

    int nb_tot_niv = 12; // nombre de niveau total pré-enregistré

    if(niv >= nb_tot_niv+1) { // si le joueur arrive au bout de la campagne
        loadColorImage(srcPath("fin.png"),R,G,B,largeur,hauteur); // image de fin
        putColorImage(0,0,R,G,B,largeur,hauteur);
        endGraphics();
    }
    else {
        play(srcPath("niv" + to_string(niv) + ".txt"),c,niv,true);
    }
}
