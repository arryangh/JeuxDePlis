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
	int idjoueur;

	string nom ;

	PaquetCarte main;

public:
	Joueur();

	virtual void jouerCoup() = 0;

	void setIdJoueur(int idJoueur);

	int getIdjoueur() const;

	void setNom(string nom);

	string getNom ();

	void setMain(PaquetCarte carte);

	PaquetCarte& getMain();
};
#endif