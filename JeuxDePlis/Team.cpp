#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Team.h"


void Team::clearPlis(){
	this->plisGagne.clear();
}

void Team::setPlisGagne(PaquetCarte* plis){
	this->plisGagne.push_back(plis);
}

PaquetCarte* Team::getPlisGagne(){
	
}

void Team::setPointManche(int nb)
{
}

int Team::getPointManche()
{
	return 0;
}

void Team::setNbPoint(int nb)
{
}

int Team::getNbPoint()
{
	return 0;
}

void Team::setTeamNom(char nom)
{
}

char Team::getTeamNom()
{
	return 0;
}

void Team::setJoueurs(vector<Joueur*> joueurs)
{
}

vector<Joueur*> Team::getJoueurs()
{
	return 0;
}
