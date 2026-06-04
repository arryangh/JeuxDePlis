#ifndef TEAM_H
#define TEAM_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "PaquetCarte.h"
#include "Joueur.h"

using namespace std;

class Team
{
private:
	vector<PaquetCarte*> plisGagne;

	int pointManche;

	int nbPoint;

	char teamNom;

	vector<Joueur*> joueurs;


public:
	void clearPlis();

	void setPlisGagne(PaquetCarte* plis);

	PaquetCarte* getPlisGagne();

	void setPointManche(int nb);

	int getPointManche();

	void setNbPoint(int nb);

	int getNbPoint();

	void setTeamNom(char nom);

	char getTeamNom();

	void setJoueurs(vector<Joueur*> joueurs);

	vector<Joueur*> getJoueurs();

};
#endif
