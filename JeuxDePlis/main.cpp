#include <iostream>
#include <windows.h>

#include "Jeu.h"
#include "TableJeu.h"
#include "DameDePique.h"
#include "PaquetCarte.h"
#include "carte.h"
#include "Team.h"
#include "joueur.h"
#include "Humain.h"
#include "IA.h"
#include "JeuManager.h"

using namespace std;

int main() {
    SetConsoleOutputCP(65001);
    JeuManager manager;

    bool continuer = true;
    while (continuer) {
        int choix = manager.ChoixDuJeu();
        Jeu* jeu = manager.InstancierJeuChoisi(choix);
        manager.ConfigurerJeu(jeu->getNbJoueurs(), jeu->getNbManche());
        manager.ConfigurerJoueurs();
        jeu->configurerTeam();
        jeu->jouer();
        delete jeu;

        cout << "\nVoulez-vous rejouer ? (1 = Oui, 0 = Non) : ";
        int rep;
        cin >> rep;
        continuer = (rep == 1);
    }
    return 0;
}