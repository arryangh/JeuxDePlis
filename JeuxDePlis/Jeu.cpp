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

size_t Jeu::getNbEquipe()
{
	size_t nbEquipes = team.size();
	return team.size();
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

void Jeu::setPointsGagnant(int newPointsGagnant)
{
	pointsGagnant = newPointsGagnant;
}

int Jeu::getPointsGagnant()
{
	return pointsGagnant;
}

void Jeu::setOrdreCarte(list<string> newOrdreCarte)
{
	ordreCarte = newOrdreCarte;
}

list<string> Jeu::getOrdreCarte(){
	return ordreCarte;
}

void Jeu::setTeam(vector<Team*> newTeam) {
	team = newTeam;
}
Joueur* Jeu::getJoueurById(int id) {
	for (Team* t : team) {
		for (const auto& joueur : t->getJoueurs()) {
			if (joueur->getIdjoueur() == id) {
				return joueur.get();
			}
		}
	}
	return nullptr; // Si aucun joueur avec cet ID n'est trouvé
}