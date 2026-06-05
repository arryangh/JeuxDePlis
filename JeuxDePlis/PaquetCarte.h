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
	std::vector<std::unique_ptr<Carte>> listeCartePaquet;


public:
	
	PaquetCarte();

	void trie(vector<Carte> ordre);

	void afficherPaquet();

	void addCarte(std::unique_ptr<Carte> carte);

	void giveCard(int carte, int paquet_carte);

	void deleteCard();

	void getListeCartePaquet();

};
#endif
