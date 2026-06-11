#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include "Carte.h"
#include "PaquetCarte.h"
#include "Jeu.h"
#include "TableJeu.h" 

Carte::Carte() {};

void Carte::setValeur(string newvaleur)
{
    valeur = newvaleur;
}

string Carte::getValeur() const
{
    return valeur;
}

void Carte::setCouleur(string newcouleur)
{
    couleur = newcouleur;
}

string  Carte::getCouleur() const
{
    return couleur;
}

bool Carte::checkCouleurPlisDansMain(const PaquetCarte& main)
{
    Jeu* jeuCourant = Jeu::getJeuCourant();
    TableJeu& table = jeuCourant->getTable();
    PaquetCarte& plis = table.getPlis();
    vector<unique_ptr<Carte>>& listeCartePlis = const_cast<vector<unique_ptr<Carte>>&>(plis.getListeCartePaquet());
    for (const auto& carte : main.getListeCartePaquet()) {
        if (carte->getCouleur() == listeCartePlis[0]->getCouleur()) {
            return true;
        }
    }
    return false;
}

string Carte::toString() const {
    return valeur + couleur;
}