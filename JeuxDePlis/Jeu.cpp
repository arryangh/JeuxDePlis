#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Jeu.h"
#include "PaquetCarte.h"

Jeu* Jeu::jeuCourant = nullptr;

void Jeu::setJeuCourant(Jeu* jeu) {
	jeuCourant = jeu;
}

Jeu::Jeu() : nbJoueurs(0), nbManche(0), pointsGagnant(0), table(nullptr) {};

Jeu* Jeu::getJeuCourant() {
	return jeuCourant;
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

bool Jeu::CompareCarte(const unique_ptr<Carte>& carte1, const unique_ptr<Carte>& carte2) {
	Jeu* jeuCourant = this->getJeuCourant();
	int hauteurCarte1 = (int)distance(jeuCourant->ordreCarte.begin(), find(jeuCourant->ordreCarte.begin(), jeuCourant->ordreCarte.end(), carte1->getValeur()));
	int hauteurCarte2 = (int)distance(jeuCourant->ordreCarte.begin(), find(jeuCourant->ordreCarte.begin(), jeuCourant->ordreCarte.end(), carte2->getValeur()));

	return hauteurCarte1 > hauteurCarte2;
}

void Jeu::addJoueur(shared_ptr<Joueur> joueur) {
	joueurs.push_back(move(joueur));
}

size_t Jeu::getNbEquipe() {
	size_t nbEquipes = team.size();
	return team.size();
}

void Jeu::setNbJoueurs(int newNb) {
	nbJoueurs = newNb;
}

int Jeu::getNbJoueurs() {
	return nbJoueurs;
}

void Jeu::setPaquetJeu(PaquetCarte newPaquetJeu) {
	paquetJeu = move(newPaquetJeu);
}

PaquetCarte& Jeu::getPaquetJeu() {
	return paquetJeu;
}

void Jeu::setNbManche(int newNb) {
	nbManche = newNb;
}

int Jeu::getNbManche() {
	return nbManche;
}

void Jeu::setPointsGagnant(int newPointsGagnant) {
	pointsGagnant = newPointsGagnant;
}

int Jeu::getPointsGagnant() {
	return pointsGagnant;
}

void Jeu::setOrdreCarte(list<string> newOrdreCarte) {
	ordreCarte = newOrdreCarte;
}

list<string> Jeu::getOrdreCarte() {
	return ordreCarte;
}

void Jeu::setTeam(vector<Team*> newTeam) {
	team = newTeam;
}

const vector<Team*>& Jeu::getTeam() const {
	return team;
}

TableJeu& Jeu::getTable() {
	return *table;
}

const vector<shared_ptr<Joueur>>& Jeu::getJoueurs() const {
	return joueurs;
}