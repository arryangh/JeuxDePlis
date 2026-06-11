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

class TableJeu;

using namespace std;

class Jeu
{
private:

	static Jeu* jeuCourant;

protected:

	int nbJoueurs;

	PaquetCarte paquetJeu;

	int nbManche;

	int pointsGagnant;

	list<string> ordreCarte;

	vector<Team*> team;

	TableJeu* table;

	vector<shared_ptr<Joueur>> joueurs;

	static void setJeuCourant(Jeu* jeu);

public:

	Jeu();

	static Jeu* getJeuCourant();

	virtual Joueur* getJoueurById(int id);

	virtual bool CompareCarte(const unique_ptr<Carte>& carte1, const unique_ptr<Carte>& carte2);

	void addJoueur(shared_ptr<Joueur> joueur);

	virtual void distribuer() = 0;

	virtual bool checkWin() = 0;

	virtual list<int> carteValide(const PaquetCarte& main, const PaquetCarte& plis) = 0;

	virtual const int playFirst() = 0; 

	virtual const int playNext() = 0;

	virtual void compterPoint() = 0;

	virtual void configurerTeam() = 0;

	virtual void jouer() = 0;

	virtual size_t getNbEquipe();

	virtual void setNbJoueurs(int newNb);

	virtual int getNbJoueurs();

	virtual void setPaquetJeu(PaquetCarte paquetJeu);

	virtual PaquetCarte& getPaquetJeu();

	virtual void setNbManche(int nbManche);

	virtual int getNbManche();

	virtual void setPointsGagnant(int pointsGagnant);

	virtual int getPointsGagnant();

	virtual void setOrdreCarte(list<string> odreCarte);

	virtual list<string> getOrdreCarte();

	virtual void setTeam(vector<Team*> newTeam);

	virtual const vector<Team*>& getTeam() const;

	virtual TableJeu& getTable();

	const vector<shared_ptr<Joueur>>& getJoueurs() const;
};
#endif
