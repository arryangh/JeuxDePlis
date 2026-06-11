#ifndef CARTE_H
#define CARTE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

class PaquetCarte;

using namespace std;

class Carte
{
private:
	string couleur;

	string valeur;

public:

	Carte();

	bool checkCouleurPlisDansMain(const PaquetCarte& main);

	void setValeur(string valeur);

	string getValeur() const;

	void setCouleur(string couleur);

	string getCouleur() const;

	string toString() const;

};
#endif