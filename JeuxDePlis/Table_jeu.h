#ifndef TABLE_JEU_H
#define TABLE_JEU_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "paquet_carte.h"
#include "Jeu.h"
#include "carte.h"

class Table_jeu
{
private:
	paquet_carte plis;


public:
	Jeu choixJeu();

	void setPlis(carte carte);

	paquet_carte getPlis();

};
#endif
