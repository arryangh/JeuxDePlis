#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <random>
#include "PaquetCarte.h"



PaquetCarte::PaquetCarte()
{
}


void PaquetCarte::afficherPaquet()
{
	for (const auto& carte : listeCartePaquet)
	{
		std::cout << "" << carte->getValeur() << "" << carte->getCouleur() << std::endl;
	}
}

void PaquetCarte::addCarte(std::unique_ptr<Carte> carte)
{
	listeCartePaquet.push_back(move(carte)); // ajoute la carte au paquet en transférant la propriété du pointeur unique
}


void PaquetCarte::giveCard(size_t indexCarte, PaquetCarte& destination)
{
	assert(indexCarte < listeCartePaquet.size());      //vérifie que l'index est valide

	destination.addCarte(std::move(listeCartePaquet[indexCarte])); // transfère la carte du paquet actuel vers le paquet de destination

	listeCartePaquet.erase(listeCartePaquet.begin() + indexCarte); // supprime le pointeur null après l'avoir transférée
}


void PaquetCarte::deleteCard()
{
	if (!listeCartePaquet.empty())
	{
		listeCartePaquet.pop_back();
	}
}

vector<unique_ptr<Carte>> PaquetCarte::getListeCartePaquet()
{
	return listeCartePaquet;
}

void PaquetCarte::MelangerPaquet()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(listeCartePaquet.begin(),listeCartePaquet.end(),gen);
}