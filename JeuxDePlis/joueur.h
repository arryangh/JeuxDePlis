#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "paquet_carte.h"
#include "carte.h"

class joueur
{
private:
	char nom ;

	paquet_carte main;


public:
	void jouerCoup();

	void setNom(char nom);

	char getNom ();

	void setMain(carte carte);

	paquet_carte getMain();

};
#endif
