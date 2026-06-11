#ifndef HUMAIN_H
#define HUMAIN_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Joueur.h"

class Humain : public Joueur
{
	int choisirCarte(const vector<int>& cartesJouables);

	void afficherCartesJouables(const std::vector<int>& jouables, const PaquetCarte& main);
	
	void jouerCoup() override;
};
#endif
