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
	void jouerCoup() override;
	void afficherCartesJouables(const std::vector<int>& jouables, const PaquetCarte& main);
	int choisirCarte(const vector<int>& cartesJouables);
};
#endif
