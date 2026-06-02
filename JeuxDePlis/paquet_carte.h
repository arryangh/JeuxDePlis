#ifndef PAQUET_CARTE_H
#define PAQUET_CARTE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "carte.h"

using namespace std;

class paquet_carte
{
private:
	vector<carte> listeCartePaquet;


public:
	void trie(vector<carte> ordre);

	void afficherPaquet();

	void addCarte(carte carte);

	void giveCard(int carte, int paquet_carte);

	void deleteCard();

	void getListeCartePaquet();

};
#endif
