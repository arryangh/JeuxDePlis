#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "PaquetCarte.h"
#include "Carte.h"

class Joueur
{
private:
	char nom ;

	PaquetCarte main;


public:
	virtual void jouerCoup() = 0;

	void setNom(char nom);

	char getNom ();

	void setMain(Carte carte);

	PaquetCarte getMain();

};
#endif
