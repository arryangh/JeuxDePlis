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
	string nom ;

	PaquetCarte main;
	
	int idjoueur;

public:
	Joueur();

	virtual void jouerCoup() = 0;

	void setNom(string nom);

	char getNom ();

	void setMain(PaquetCarte carte);

	PaquetCarte& getMain();

	void setIdJoueur(int idJoueur);

	int getIdjoueur() const;

};
#endif
