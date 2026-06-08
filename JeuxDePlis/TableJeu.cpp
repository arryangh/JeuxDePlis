#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "TableJeu.h"

TableJeu::TableJeu() {};


void TableJeu::setPlis(PaquetCarte paquet_carte) {
	TableJeu::paquetCarte = paquet_carte;
}

PaquetCarte TableJeu::getPlis(){
	return TableJeu::paquetCarte;
}
