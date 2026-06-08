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

	vector<unique_ptr<Carte>> ordreCarte;

	vector<Team*> team;

	// constructeur privé pour le singleton
	Jeu();


public:

	static Jeu* getInstance() {
		if (jeu == nullptr) {
			jeu = new Jeu();
		}
		return jeu;
	}

	virtual void distribuer();

	virtual void jouerCarte() = 0;

	virtual void checkWin() = 0;

	virtual bool checkPlis() = 0;

	// ne doit pas être virtuelle pure, sinon ça rend la classe abstraite (et donc non instanciable)
	virtual Joueur playFirst(); 

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
