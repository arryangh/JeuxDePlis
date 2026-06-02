#ifndef CARTE_H
#define CARTE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

class carte
{
private:
	int couleur;

	int valeur;


public:
	bool carteJouable();

	void setValeur(int valeur);

	int getValeur();

	void setCouleur(int couleur);

	int getCouleur();

};
#endif
