#ifndef JEU_H
#define JEU_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include <memory> 
#include "PaquetCarte.h"
#include "Carte.h"
#include "Joueur.h"
#include "Team.h"

using namespace std;

class Jeu
{
private:
	// variable de classe 
	static Jeu* jeu;

	int distribution;

	int nbJoueurs;

	PaquetCarte paquetJeu;

	int nbManche;

	int pointsGagnant;

	list<string> ordreCarte;

	vector<Team*> team;

	// constructeur privé pour le singleton
	Jeu();


public:

	static Jeu* getInstance();

	virtual void distribuer() = 0;

	virtual void jouerCarte() = 0;

	virtual void checkWin() = 0;

	virtual bool checkPlis() = 0;

	// ne doit pas être virtuelle pure, sinon ça rend la classe abstraite (et donc non instanciable)
	const int playFirst(); 

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

	void setOrdreCarte(list<string> odreCarte);

	list<string> getOrdreCarte();

	void setTeam(vector<Team*> newTeam);

	vector<Team*> getTeam() { return team; };
};
#endif
