#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Joueur.h"


Joueur::Joueur() {};

void Joueur::setNom(string nom){
	this->nom = nom;
}

string Joueur::getNom (){
	return this->nom;
}

void Joueur::setMain(PaquetCarte carte){
	this->main = move(carte);
}

PaquetCarte& Joueur::getMain(){
	return this->main;
}

void Joueur::setIdJoueur(int idJoueur) {
	this->idjoueur = idJoueur;
}

int Joueur::getIdjoueur() const {
	return idjoueur;
}