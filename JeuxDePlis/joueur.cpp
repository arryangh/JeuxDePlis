#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Joueur.h"


Joueur::Joueur() {};

void Joueur::setNom(char nom){
	this->nom = nom;
}

char Joueur::getNom (){
	return this->nom;
}

void Joueur::setMain(PaquetCarte carte){
	this->main = carte;
}

PaquetCarte Joueur::getMain(){
	return this->main;
}
