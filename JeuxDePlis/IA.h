#ifndef I_A_H
#define I_A_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include <random>

#include "Joueur.h"

class IA : public Joueur
{
private :
	mt19937 gen{ random_device{}() };
public :
	void jouerCoup() override;
	int randomIndex(int max);
};
#endif
