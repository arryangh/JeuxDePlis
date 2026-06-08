#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Jeu.h"
#include "PaquetCarte.h"

		
Jeu::Jeu() {};

void Jeu::setDistribution(int newNb){
	distribution = newNb;
}

int Jeu::getDistribution()
{
	return distribution;
}

void Jeu::setNbJoueurs(int newNb){
	nbJoueurs = newNb;
}

int Jeu::getNbJoueurs(){
	return nbJoueurs;
}

void Jeu::setPaquetJeu(PaquetCarte newPaquetJeu){
	paquetJeu = newPaquetJeu;
}

PaquetCarte Jeu::getPaquetJeu()
{
	return paquetJeu;
}

void Jeu::setNbManche(int newNb){
	nbManche = newNb;
}

int Jeu::getNbManche()
{
	return nbManche;
}

void Jeu::setPointsGagnant(int pointsGagnant)
{
}

int Jeu::getPointsGagnant()
{
	return 0;
}

void Jeu::setOrdreCarte(vector<Carte> odreCarte)
{
}

vector<unique_ptr<Carte>> Jeu::getOrdreCarte(){
	return ordreCarte;
}

void setTeam(vector<Team> newTeam) {

}