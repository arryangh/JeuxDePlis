#ifndef JEUMANAGER_H
#define JEUMANAGER_H

#include "Jeu.h"

class JeuManager {
public :
	void afficherText(string s);

	int ChoixDuJeu();

	Jeu* InstancierJeuChoisi(int choix);

	void ConfigurerJeu(int nbJoueurs, int nbManches);

	void ConfigurerJoueurs();
};
#endif