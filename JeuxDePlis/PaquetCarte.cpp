#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include "PaquetCarte.h"
//pas besoin de faire add et delete car on modifie juste le pointeur
PaquetCarte::PaquetCarte()
{
}

void PaquetCarte::trie(vector<Carte> ordre)
{
}

void PaquetCarte::afficherPaquet()
{
}

void PaquetCarte::addCarte(std::unique_ptr<Carte> carte)
{
	listeCartePaquet.push_back(std::move(carte));
}

void PaquetCarte::giveCard(int carte, int paquet_carte)
{
}

void PaquetCarte::deleteCard()
{
	if (!listeCartePaquet.empty())
	{
		listeCartePaquet.pop_back();
	}
}

std::vector<std::unique_ptr<Carte>> PaquetCarte::getListeCartePaquet()
{
	return listeCartePaquet;
}
