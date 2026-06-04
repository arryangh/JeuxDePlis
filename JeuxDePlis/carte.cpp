#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "carte.h"

void carte::setValeur(int newvaleur)
{
	valeur = newvaleur;
}

int carte::getValeur()
{
	return valeur;
}

void carte::setCouleur( Couleur newcouleur)
{
	couleur = newcouleur;
}

carte::Couleur  carte::getCouleur()
{
	return couleur;
}

