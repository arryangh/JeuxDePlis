#ifndef CARTE_H
#define CARTE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

using namespace std;
class Carte
{
private:
	string couleur;
	string valeur;


public:

	Carte();

	void setValeur(string valeur);

	string getValeur();

	void setCouleur(string couleur);

	string getCouleur();

	bool checkCouleurPlisDansMain( const PaquetCarte& main);

	string toString() const;

};
#endif
