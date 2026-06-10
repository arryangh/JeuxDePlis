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
	 
	list<string> ordreCarte = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Valet", "Dame", "Roi", "As" };
	list<string> Couleur = { "Pique", "Coeur", "Carreau", "Trèfle" };

	bool Coeur_Brise;

	DameDePique();

public :

	static DameDePique* getInstance() {
		if (dameDePique == nullptr) {
			dameDePique = new DameDePique();
		}
		return dameDePique;
	}
	void creerPaquetJeu();

	void distribuer() override;

	void jouerCarte() override;

	void checkWin() override;

	int gagnantPlis();

	list<int> carteValide(const PaquetCarte& main, const PaquetCarte& plis) override;//carte jouable 

	const int playFirst() override;

	const int playNext() ;

	void compterPoint() override;

	bool checkCoeurBrise();


};
#endif
