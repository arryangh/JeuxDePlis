#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "IA.h"
#include "Jeu.h"

void IA::jouerCoup() {
	Jeu* jeuCourant = Jeu::getJeuCourant();
	TableJeu table = jeuCourant->getTable();
	PaquetCarte plis = table.getPlis();
	vector<unique_ptr<Carte>> cartesJouables;
	for (const auto& carte : plis.getListeCartePaquet()) {

	}


}




