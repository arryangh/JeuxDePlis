#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include "Team.h"
#include "DameDePique.h"

DameDePique::DameDePique() {
}
void DameDePique::creerPaquetJeu() {
	for (const string& newcouleur : Couleur) {
		for (const string& newvaleur : ordreCarte) {
			unique_ptr<Carte> newcarte = make_unique<Carte>();
			newcarte->setCouleur(newcouleur);
			newcarte->setValeur(newvaleur);
			getPaquetJeu().addCarte(move(newcarte));
		}
	}
}


void DameDePique::distribuer() {
	int i = 0;

	while (getPaquetJeu().PaquetSize() > 0) {
		getPaquetJeu().giveCard(0, getJoueurById(i)->getMain());
		i = (i + 1) % getNbJoueurs();
	}
}

void DameDePique::jouerCarte() {}

void DameDePique::checkWin() {}

bool DameDePique::checkPlis() {}

const int DameDePique::playFirst() {}

void DameDePique::compterPoint() {}


