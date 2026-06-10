#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Humain.h"
#include "Jeu.h"
#include "TableJeu.h" 


#include <iostream>

void Humain::jouerCoup() {

    Jeu* jeuCourant = Jeu::getJeuCourant();
    TableJeu& table = jeuCourant->getTable();
    PaquetCarte& plis = table.getPlis();
    list<int> cartesJouables = jeuCourant->carteValide(getMain(), plis);

    vector<int> jouables(cartesJouables.begin(), cartesJouables.end());

    afficherCartesJouables(jouables, getMain());

    int indexCarteMain = choisirCarte(jouables);

    Carte& carteChoisie =
        *getMain().getListeCartePaquet()[indexCarteMain];

    plis.giveCard(indexCarteMain, getMain());

    std::cout << "Carte jouee : " << carteChoisie.toString() << "\n";
}

void Humain::afficherCartesJouables( const std::vector<int>& jouables, const PaquetCarte& main){
    std::cout << "Cartes jouables :\n";

    for (int i = 0; i < jouables.size(); i++) {
        const Carte& c = *main.getListeCartePaquet()[jouables[i]];
        std::cout << i << " -> " << c.toString() << "\n";
    }
}

int Humain::choisirCarte(const vector<int>& cartesJouables) {
    cout << "Cartes jouables:\n";

    for (int i = 0; i < cartesJouables.size(); i++) {
        cout << i << " -> " << cartesJouables[i] << "\n";
    }

    int choix;
    cin >> choix;

    return cartesJouables[choix];
}
