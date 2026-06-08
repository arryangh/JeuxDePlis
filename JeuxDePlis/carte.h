#ifndef CARTE_H
#define CARTE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

class Carte
{
private:
	enum Couleur {
		PIQUE,
		TREFLE,
		COEUR,
		CARREAU
	};

	Couleur couleur;
	int valeur;


public:

	Carte();

	void setValeur(int valeur);

	int getValeur();

	void setCouleur(Couleur couleur);

	Couleur getCouleur();

};
#endif
