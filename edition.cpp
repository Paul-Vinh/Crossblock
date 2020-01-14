#include "edition.h"

void edition_case(Image<Color>& I, int i, int j, Config& c) { // colore en bleu ou blanc la case concernée, pointée à la souris
    int largeur = c.get_Largeur();
    int hauteur = c.get_Hauteur();
    int N = c.get_N();

    Color C;
    int x = largeur*i/N; // abscisse a partir des numéros de cases
    int y = hauteur*j/N; // ordonnee a partir des numéros de cases

    if(c.get_elem_cas(i,j) == 0) { // rend la case active
        C = BLUE;
        c.set_elem_cas(i,j,1);
    }

    else if(c.get_elem_cas(i,j) == 1) { // rend la case non active
        C = WHITE;
        c.set_elem_cas(i,j,0);
    }

    for(int k = x; k< x + largeur/N - 4; k++) {
        for(int l = y; l< y + hauteur/N - 4; l++) {
            I(k,l) = C;
        }
    }
    fillRect(x,y,largeur/N-5,hauteur/N-5,C);
}

void sauvegarde(string nomfichier, int nbre, Config& c) { // sauvegarde la map en fichier .txt
    int N = c.get_N();

    // Ouverture d'un flux pour ecrire dans un fichier
    ofstream monFlux(stringSrcPath(nomfichier), ios::out);

    if(monFlux)
    {
        monFlux << nbre << endl;
        string ligne;
        for(int j=0; j<N; j++) {
            ligne = "";
            for(int i=0; i<N; i++) {
                if(c.get_elem_cas(i,j) == 1)
                    ligne += " 1 ";
                else
                    ligne += " 0 ";
            }
            monFlux << ligne << endl;
        }
        monFlux.close();
    }

    else
    {
        cerr << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }
}
