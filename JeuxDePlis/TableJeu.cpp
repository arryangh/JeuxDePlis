#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "TableJeu.h"

TableJeu::TableJeu() {};


void TableJeu::setPlis(PaquetCarte& paquet_carte) {
	plis = move(paquet_carte);
}

PaquetCarte& TableJeu::getPlis(){
	return TableJeu::plis;
}

void TableJeu::setIdPremierJoueur(int id) {
	TableJeu::idpremierJoueur = id;
}

int TableJeu::getIdPremierJoueur() {
	return TableJeu::idpremierJoueur;
}	

