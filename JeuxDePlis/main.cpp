#include <iostream>
#include <windows.h>

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
    SetConsoleOutputCP(65001);
    JeuManager manager = JeuManager();
    int choix = manager.ChoixDuJeu();
    manager.afficherText("chois du jeu ok");
    Jeu* jeu = manager.InstancierJeuChoisi(choix);
    manager.afficherText("jeu instancier");

    manager.afficherText("Je suis dans la boucle avant configuration");
    manager.ConfigurerJeu(jeu->getNbJoueurs(), jeu->getNbManche());
    manager.afficherText("Config jeu ok");
    manager.ConfigurerJoueurs();
    manager.afficherText("Config joueur ok");
    

    jeu->configurerTeam();


    jeu->jouer(); // boucle principal du jeu
    manager.afficherText("Fin jeu");
    delete jeu;
    return 0;
}