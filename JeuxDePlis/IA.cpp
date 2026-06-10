#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include <random>

#include "IA.h"
#include "Jeu.h"

void IA::jouerCoup() {
	Jeu* jeuCourant = Jeu::getJeuCourant();
	TableJeu& table = jeuCourant->getTable();
	PaquetCarte& plis = table.getPlis();
	list<int> cartesJouables = jeuCourant->carteValide(getMain(), plis);

	vector<int> jouables(cartesJouables.begin(), cartesJouables.end());

	int indexListe = randomIndex(jouables.size());

	int indexCarteMain = jouables[indexListe];

	plis.giveCard(indexCarteMain, getMain());
}

int IA::randomIndex(int max) {
	uniform_int_distribution<> dist(0, max - 1);
	return dist(gen);
}




