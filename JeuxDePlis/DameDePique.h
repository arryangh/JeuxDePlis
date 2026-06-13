#ifndef DAME_DE__PIQUE_H
#define DAME_DE__PIQUE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Jeu.h"

using namespace std;

class DameDePique : public Jeu
{
private:
	static DameDePique* dameDePique;

	list<string> Couleur = { "Pique", "Coeur", "Carreau", "Trèfle" };

	bool Coeur_Brise;

	bool premierPli;

public:

	DameDePique();

	void distribuer() override;

	bool checkWin() override;

	list<int> carteValide(const PaquetCarte& main, const PaquetCarte& plis) override;//carte jouable 

	const int playFirst() override;

	const int playNext() override;

	void compterPoint() override;

	void configurerTeam() override;

	void jouer() override;

	void echangerCartes(int numeroManche) override;

	static Jeu* getInstance();

	void creerPaquetJeu();

	int gagnantPlis();

	bool checkCoeurBrise();

	void afficherScores();

	void afficherPliEnCours(int premierJoueur);

};
#endif