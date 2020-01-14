#ifndef CONFIG_H
#define CONFIG_H

#include <Imagine/Images.h>
using namespace Imagine;
#include <stdio.h>
#include <string>
using namespace std;

class Config {
    int largeur;
    int hauteur;
    int N;
    int cas[10][10];
public:
    Config();
    int get_Largeur();
    int get_Hauteur();
    int get_N();
    int &get_elem_cas(int i, int j);
    void set_elem_cas(int i, int j, int nb);
};

#endif // CONFIG_H
