#include <iostream>

// les classes 
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
    JeuManager manager = JeuManager();
    int choix = manager.ChoixDuJeu();

    Jeu* jeu = manager.InstancierJeuChoisi(choix);

    if (jeu != nullptr) {
        manager.ConfigurerJeu(jeu->getNbJoueurs(), jeu->getNbManche());
        manager.ConfigurerJoueurs();
        //jeu->jouer(); // boucle principal du jeu
        delete jeu;
    }



    return 0;
}