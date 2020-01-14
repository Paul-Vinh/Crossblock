#include <cstdlib>
#include <ctime>
#include "param.h"
#include "jeu.h"
using namespace std;

Param txt_to_image(string nomFichier, Config& c) {
    int largeur = c.get_Largeur();
    int hauteur = c.get_Hauteur();

    ifstream fichier(nomFichier);
    Image<Color> I(largeur, hauteur);
    I.fill(WHITE);
    if(fichier)
    {
        int i = 0; // compteur
        string ligne; // Une variable pour stocker les lignes lues
        string number;
        getline(fichier, number);  // on lit le nombre de carres a couper
        int nombre = stoi(number); // transformation de string en int
        while(getline(fichier, ligne)) // Tant qu'on n'est pas à la fin, on lit !
        {
            coloriage_cases(i,ligne,I,c);
            i++;
        }
        Param pa;
        pa.I = I;
        pa.nbre = nombre;
        return(pa);
    }
    else {
       cerr << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }
}
