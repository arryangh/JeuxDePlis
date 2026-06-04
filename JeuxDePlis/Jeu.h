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

using namespace std;

class Jeu
{
private:
	int distribution;

	int nbJoueurs;

	PaquetCarte paquetJeu;

	int nbManche;

	int pointsGagnant;

	vector<Carte> ordreCarte;


public:
	void distribuer();

	void jouerCarte();

	void checkWin();

	bool checkPlis();

	Joueur playFirst();

	void compterPoint();

	void setDistribution(int distribution);

	int getDistribution();

	void setNbJoueurs();

	int getNbJoueurs();

	void setPaquetJeu(PaquetCarte paquetJeu);

	PaquetCarte getPaquetJeu();

	void setNbManche(int nbManche);

	int getNbManche();

	void setPointsGagnant(int pointsGagnant);

	int getPointsGagnant();

	void setOrdreCarte(vector<Carte> odreCarte);

	int getOrdreCarte();

};
#endif
