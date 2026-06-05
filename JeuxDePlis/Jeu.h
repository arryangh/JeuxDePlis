#ifndef JEU_H
#define JEU_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "PaquetCarte.h"
#include "Carte.h"
#include "Joueur.h"
#include "Team.h"

using namespace std;

class Jeu
{
private:
	int distribution;

	int nbJoueurs;

	PaquetCarte paquetJeu;

	int nbManche;

	int pointsGagnant;

	vector<unique_ptr<Carte>> ordreCarte;

	vector<Team*> team;


public:
	virtual void distribuer() = 0;

	virtual void jouerCarte() = 0;

	virtual void checkWin() = 0;

	virtual bool checkPlis() = 0;

	virtual Joueur playFirst() = 0;

	virtual void compterPoint() = 0;

	void setDistribution(int newNb);

	int getDistribution();

	void setNbJoueurs(int newNb);

	int getNbJoueurs();

	void setPaquetJeu(PaquetCarte paquetJeu);

	PaquetCarte getPaquetJeu();

	void setNbManche(int nbManche);

	int getNbManche();

	void setPointsGagnant(int pointsGagnant);

	int getPointsGagnant();

	void setOrdreCarte(vector<Carte> odreCarte);

	vector<unique_ptr<Carte>> getOrdreCarte();

	void setTeam(vector<Team> newTeam);

	vector<Team*> getTeam() { return team; };
};
#endif
