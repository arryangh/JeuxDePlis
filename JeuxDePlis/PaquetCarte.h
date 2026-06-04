#ifndef PAQUET_CARTE_H
#define PAQUET_CARTE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Carte.h"

using namespace std;

class PaquetCarte
{
private:
	vector<Carte> listeCartePaquet;


public:
	void trie(vector<Carte> ordre);

	void afficherPaquet();

	void addCarte(Carte carte);

	void giveCard(int carte, int paquet_carte);

	void deleteCard();

	void getListeCartePaquet();

};
#endif
