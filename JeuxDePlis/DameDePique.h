#ifndef DAME_DE__PIQUE_H
#define DAME_DE__PIQUE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Jeu.h"

class DameDePique : public Jeu
{
private:
	static DameDePique* dameDePique;

	bool Coeur_Brise;

	DameDePique();

public :

	DameDePique* getInstance() {
		if (dameDePique == nullptr) {
			dameDePique = new DameDePique();
		}
		return dameDePique;
	}
	void distribuer() override;

	void jouerCarte() override;

	void checkWin() override;

	bool checkPlis() override;

	const int playFirst() override;

	void compterPoint() override;
};
#endif
