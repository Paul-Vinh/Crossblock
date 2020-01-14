// Imagine++ project
// Project:  Crossblock
// Author:   LÊ Paul-Vinh et QUILY Ludovic
// Date:     2019/06/06

#include <Imagine/Graphics.h>
#include <Imagine/Images.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>

#include "jeu.h"
#include "edition.h"
#include "config.h"
#include "param.h"
#include "point.h"

using namespace std;
using namespace Imagine;

int choix_niveau() { // selection des niveaux a la souris (menu)
    Event e;
    int x,y;
    int niveau = 0;

    do {
        getEvent(0, e);
        if(e.type==EVT_BUT_ON) { // premier point de la ligne
            x = e.pix[0];
            y = e.pix[1];

            if(y >= 100 && y <= 210) {
                if(x >= 70 && x <= 140)
                    niveau = 1;
                else if(x >= 190 && x <= 260)
                    niveau = 2;
                else if(x >= 290 && x <= 380)
                    niveau = 3;
                else if(x >= 410 && x <= 490)
                    niveau = 4;
                else if(x >= 520 && x <= 600)
                    niveau = 5;
                else if(x >= 650 && x <= 730)
                    niveau = 6;
            }

            else if(y >= 280 && y <= 410) {
                if(x >= 70 && x <= 140)
                    niveau = 7;
                else if(x >= 190 && x <= 260)
                    niveau = 8;
                else if(x >= 290 && x <= 380)
                    niveau = 9;
                else if(x >= 410 && x <= 490)
                    niveau = 10;
                else if(x >= 520 && x <= 600)
                    niveau = 11;
                else if(x >= 650 && x <= 730)
                    niveau = 12;
            }
        }
    } while(e.type!=EVT_BUT_OFF || niveau == 0);
    return(niveau);
}

int main() {
    Config c;
    int largeur = c.get_Largeur();
    int hauteur = c.get_Hauteur();
    int N = c.get_N();

    int mode = 0;
    string nomFichier;
    // image du menu
    byte* R = new byte[largeur*hauteur];
    byte* G = new byte[largeur*hauteur];
    byte* B = new byte[largeur*hauteur];

    int w_acc = 800, h_acc = 450;
    Window w = openWindow(w_acc,h_acc);
    loadColorImage(srcPath("accueil.png"),R,G,B,w_acc,h_acc); // image d'accueil
    putColorImage(0,0,R,G,B,w_acc,h_acc);

    // gestion des evenements clavier
    bool sortie = false;
    do {
        if(getKey() == 99) { // Campagne
            mode = 1;
            sortie = true;
        }
        else if(getKey() == 103) { // Edition de grille
            mode = 2;
            sortie = true;
        }
    } while(!sortie); // 99 : 'C' et 103 : 'G'

    closeWindow(w);

    // Ouverture de la fenetre
    Window W2 = openWindow(largeur,hauteur);
    setActiveWindow(W2);

    if(mode == 1) { // mode campagne
            closeWindow(W2);

            int w_c = 800, h_c = 450;
            Window W3 = openWindow(w_c,h_c);
            loadColorImage(srcPath("choix_niv.png"),R,G,B,w_c,h_c); // image d'accueil
            putColorImage(0,0,R,G,B,w_c,h_c);
            int niv = 0;
            cout << "Choisissez votre niveau :" << endl;
            niv = choix_niveau();
            cout << niv << endl;

            closeWindow(W3);
            Window W4 = openWindow(largeur,hauteur);
            setActiveWindow(W4);

            play(srcPath("niv" + to_string(niv) + ".txt"),c,niv,true);
            // play(srcPath(".txt"),c,0,false); // si le joueur veut jouer a un niveau édité
    }

    else if(mode == 2) { // mode edition
        Image<Color> I(largeur,hauteur);
        int x0, y0;
        while(getMouse(x0, y0) != 3) { // tant qu'il y a des clics gauches
            int i = x0*N / largeur;
            int j = y0*N / hauteur;
            edition_case(I,i,j,c);
        }

        // nombre de cases a casser pour le niveau
        int nbre_cases;
        cout << "Entrez le nombre de cases a casser a la fois :";
        cin >> nbre_cases;
        cout << endl;

        cout << "Entrez le nom du fichier a sauvegarder :";
        cin >> nomFichier;
        nomFichier += ".txt";
        sauvegarde(nomFichier,nbre_cases,c);
    }
    endGraphics();
    return 0;
}
