#include <iostream>
#include "projet.h"
using namespace std;

int main()
{
    start w;
    //w.MessageDeDebut();

    cout << " \n  \t \t \t - Player Vs Computer \n"
         << endl;
    cout << " Remarque: le programme ne contient pas l'algorithme Alphabeta " << endl;
    cout << " \t \t pour tester le fonctionnement de Minimax  donner  \n  \t  \t la valeur 2 a la taille de tablier   " << endl;
    cout << " \n Donner la taille de Tablier : \t ";
    cin >> w.size;
    w.creationPlateau(w.size);
    //w.AfficherPlateau();

    /*w.plateau[1][3]='1';
//w.bridge_array.push_back(103);
w.plateau[2][4]='0';

w.plateau[2][6]='0';
//w.plateau[1][5]='1';
//w.fork_array.push_back(105);
w.plateau[3][7]='0';
w.plateau[3][5]='1';
w.plateau[4][4]='0';
w.plateau[1][7]='1';
//w.bridge_array.push_back(107);*/
    //w.plateau[1][4]='1';
    //w.bridge_array.push_back(104);*/
    w.play();
}
