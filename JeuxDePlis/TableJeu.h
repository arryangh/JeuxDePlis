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
	PaquetCarte paquetCarte;

public:
	
	TableJeu();

	void setPlis(PaquetCarte paquet_carte);

	PaquetCarte getPlis();

};
#endif
