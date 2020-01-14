#include <cstdlib>
#include <ctime>
#include "config.h"
using namespace std;

Config::Config() {
    largeur = 600;
    hauteur = 600;
    N = 10;

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            set_elem_cas(i,j,0);
        }
    }
}

int Config::get_Largeur() {
    return largeur;
}

int Config::get_Hauteur() {
    return hauteur;
}

int Config::get_N() {
    return N;
}

int &Config::get_elem_cas(int i, int j) {
    return(cas[i][j]);
}

void Config::set_elem_cas(int i, int j, int nb) {
    cas[i][j] = nb;
}
