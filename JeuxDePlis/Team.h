#ifndef TEAM_H
#define TEAM_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "paquet_carte.h"
#include "joueur.h"

using namespace std;

class Team
{
private:
	vector<paquet_carte> plisGagne;

	int pointManche;

	int nbPoint;

	char teamNom;

	vector<joueur> joueurs;


public:
	void clearPlis();

	void setPlisGagne(paquet_carte plis);

	paquet_carte getPlisGagne();

	void setPointManche(int nb);

	int getPointManche();

	void setNbPoint(int nb);

	int getNbPoint();

	void setTeamNom(char nom);

	char getTeamNom();

	void setJoueurs(vector<joueur> joueurs);

	vector<joueur> getJoueurs();

};
#endif
