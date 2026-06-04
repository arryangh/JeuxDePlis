#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Joueur.h"




void Joueur::setNom(char nom){
	this->nom = nom;
}

char Joueur::getNom (){
	return this->nom;
}

void Joueur::setMain(Carte carte){
	// il faut la classe PaquerCarte
}

paquet_carte Joueur::getMain(){
	return this->main;
}
