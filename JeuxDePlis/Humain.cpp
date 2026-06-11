#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Humain.h"
#include "Jeu.h"
#include "TableJeu.h"

void Humain::jouerCoup() {
    Jeu* jeuCourant = Jeu::getJeuCourant();
    TableJeu& table = jeuCourant->getTable();
    PaquetCarte& plis = table.getPlis();
    list<int> cartesJouables = jeuCourant->carteValide(getMain(), plis);

    vector<int> jouables(cartesJouables.begin(), cartesJouables.end());

    // Afficher les cartes déjà posées sur la table
    if (plis.PaquetSize() > 0) {
        cout << "Sur la table : ";
        for (size_t i = 0; i < plis.PaquetSize(); i++) {
            const auto& c = plis.getListeCartePaquet()[i];
            cout << c->getValeur() << " de " << c->getCouleur() << "  ";
        }
        cout << endl;
    }
    else {
        cout << "Vous êtes le premier à jouer ce pli." << endl;
    }

    afficherCartesJouables(jouables, getMain());

    int indexCarteMain = choisirCarte(jouables);

    // On copie les infos avant giveCard (la carte sera déplacée après)
    string valeur = getMain().getListeCartePaquet()[indexCarteMain]->getValeur();
    string couleur = getMain().getListeCartePaquet()[indexCarteMain]->getCouleur();

    getMain().giveCard(indexCarteMain, plis);

    cout << getNom() << " joue : " << valeur << " de " << couleur << endl;
}

void Humain::afficherCartesJouables(const std::vector<int>& jouables, const PaquetCarte& main) {
    std::cout << "[" << getNom() << "] Vos cartes jouables :" << endl;
    for (int i = 0; i < (int)jouables.size(); i++) {
        const auto& c = main.getListeCartePaquet()[jouables[i]];
        std::cout << "  " << i << " -> " << c->getValeur() << " de " << c->getCouleur() << "\n";
    }
}

int Humain::choisirCarte(const vector<int>& cartesJouables) {
    int choix = -1;
    while (choix < 0 || choix >= (int)cartesJouables.size()) {
        cout << "Votre choix (0-" << cartesJouables.size() - 1 << ") : ";
        cin >> choix;
        if (choix < 0 || choix >= (int)cartesJouables.size()) {
            cout << "Choix invalide, réessayez." << endl;
        }
    }
    return cartesJouables[choix];
}