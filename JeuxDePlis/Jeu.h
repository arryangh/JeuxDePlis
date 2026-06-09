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
#include "TableJeu.h"

using namespace std;

class Jeu
{
protected:

	int distribution;

	int nbJoueurs;

	PaquetCarte paquetJeu;

	int nbManche;

	int pointsGagnant;

	list<string> ordreCarte;

	vector<Team*> team;

	TableJeu* table;


public:

	Jeu();

	virtual void distribuer() = 0;

	virtual void jouerCarte() = 0;

	virtual void checkWin() = 0;

	virtual bool checkPlis() = 0;

	virtual const int playFirst() = 0; 

	virtual void compterPoint() = 0;

	void setDistribution(int newNb);

	int getDistribution();

	void setNbJoueurs(int newNb);

	int getNbJoueurs();

	size_t getNbEquipe();

	void setPaquetJeu(PaquetCarte paquetJeu);

	PaquetCarte getPaquetJeu();

	void setNbManche(int nbManche);

	int getNbManche();

	void setPointsGagnant(int pointsGagnant);

	int getPointsGagnant();

	void setOrdreCarte(list<string> odreCarte);

	list<string> getOrdreCarte();

	void setTeam(vector<Team*> newTeam);

	const std::vector<Team*>& getTeam() const {
		return team;
	}
	Joueur* getJoueurById(int id);
	
	TableJeu& getTable() {
		return *table;
	}	

	bool CompareCarte(const unique_ptr<Carte>& carte1, const unique_ptr<Carte>& carte2);
};
#endif
