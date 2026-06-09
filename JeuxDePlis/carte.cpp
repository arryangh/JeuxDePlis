#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include "Carte.h"


Carte::Carte() {};

void Carte::setValeur(string newvaleur)
{
	valeur = newvaleur;
}

string Carte::getValeur()
{
	return valeur;
}

void Carte::setCouleur( string newcouleur)
{
	couleur = newcouleur;
}

string  Carte::getCouleur()
{
	return couleur;
}

