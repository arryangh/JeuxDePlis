#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Carte.h"

void Carte::setValeur(int newvaleur)
{
	valeur = newvaleur;
}

int Carte::getValeur()
{
	return valeur;
}

void Carte::setCouleur( Couleur newcouleur)
{
	couleur = newcouleur;
}

Carte::Couleur  Carte::getCouleur()
{
	return couleur;
}

