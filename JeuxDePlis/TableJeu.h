#ifndef TABLE_JEU_H
#define TABLE_JEU_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "PaquetCarte.h"
#include "Jeu.h"
#include "Carte.h"

class TableJeu
{
private:
	PaquetCarte plis;


public:
	Jeu choixJeu();

	void setPlis(Carte carte);

	PaquetCarte getPlis();

};
#endif
