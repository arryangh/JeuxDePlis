#ifndef JEU_H
#define JEU_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "paquet_carte.h"
#include "carte.h"
#include "joueur.h"

using namespace std;

class Jeu
{
private:
	int distribution;

	int nbJoueurs;

	paquet_carte paquetJeu;

	int nbManche;

	int pointsGagnant;

	vector<carte> ordreCarte;


public:
	void distribuer();

	void jouerCarte();

	void checkWin();

	bool checkPlis();

	joueur playFirst();

	void compterPoint();

	void setDistribution(int distribution);

	int getDistribution();

	void setNbJoueurs();

	int getNbJoueurs();

	void setPaquetJeu(paquet_carte paquetJeu);

	paquet_carte getPaquetJeu();

	void setNbManche(int nbManche);

	int getNbManche();

	void setPointsGagnant(int pointsGagnant);

	int getPointsGagnant();

	void setOrdreCarte(vector<carte> odreCarte);

	int getOrdreCarte();

};
#endif
