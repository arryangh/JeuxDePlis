#include <string>
#include <vector>
#include <list>
#include <iostream>

#include "Humain.h"
#include "Jeu.h"
#include "TableJeu.h"
#include "Team.h"

static void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

static void attendreEntree(const string& message) {
    cout << message;
    cin.clear();
    cin.ignore(1000, '\n');
}

// Affiche les scores de tous les joueurs
static void afficherScores() {
    Jeu* jeu = Jeu::getJeuCourant();
    cout << "=== SCORES ===" << endl;
    for (size_t i = 0; i < jeu->getNbEquipe(); i++) {
        const auto& t = jeu->getTeam()[i];
        cout << "  " << t->getTeamNom() << " : " << t->getNbPoint() << " pts" << endl;
    }
    cout << endl;
}

// Affiche les cartes déjà posées sur la table
static void afficherPliEnCours(const PaquetCarte& plis, int idPremierJoueur) {
    Jeu* jeu = Jeu::getJeuCourant();
    if (plis.PaquetSize() == 0) {
        cout << "Pli : vous commencez !" << endl;
    }
    else {
        cout << "Pli en cours : ";
        for (size_t i = 0; i < plis.PaquetSize(); i++) {
            const auto& c = plis.getListeCartePaquet()[i];
            string nom = jeu->getJoueurById((idPremierJoueur + (int)i) % jeu->getNbJoueurs())->getNom();
            cout << nom << " [" << c->getValeur() << " de " << c->getCouleur() << "]  ";
        }
        cout << endl;
    }
}

int Humain::choisirCarte(const vector<int>& cartesJouables) {
    int choix = -1;
    while (choix < 0 || choix >= (int)cartesJouables.size()) {
        cout << "Votre choix (0-" << (int)cartesJouables.size() - 1 << ") : ";
        cin >> choix;
        if (choix < 0 || choix >= (int)cartesJouables.size())
            cout << "Choix invalide, réessayez." << endl;
    }
    return cartesJouables[choix];
}

void Humain::afficherCartesJouables(const vector<int>& jouables, const PaquetCarte& main) {
    cout << "\nCartes jouables :" << endl;
    for (int i = 0; i < (int)jouables.size(); i++) {
        const auto& c = main.getListeCartePaquet()[jouables[i]];
        cout << "  " << i << " -> " << c->getValeur() << " de " << c->getCouleur() << endl;
    }
}

void Humain::jouerCoup() {
    Jeu* jeuCourant = Jeu::getJeuCourant();
    TableJeu& table = jeuCourant->getTable();
    PaquetCarte& plis = table.getPlis();
    int idPremierJoueur = table.getIdPremierJoueur();

    // Écran de transition : on cache le jeu du joueur précédent
    clearConsole();
    cout << "=== Au tour de : " << getNom() << " ===" << endl;
    attendreEntree("(Appuyez sur Entrée pour voir votre jeu...)");

    // Affichage du tour
    clearConsole();
    cout << "=== Tour de : " << getNom() << " ===" << endl << endl;

    afficherScores();
    afficherPliEnCours(plis, idPremierJoueur);

    // Main complète
    cout << "\nVotre main (" << getMain().PaquetSize() << " cartes) :" << endl;
    const auto& cartes = getMain().getListeCartePaquet();
    for (size_t i = 0; i < cartes.size(); i++)
        cout << "  [" << i << "] " << cartes[i]->getValeur() << " de " << cartes[i]->getCouleur() << endl;

    // Cartes jouables et choix
    list<int> cartesJouables = jeuCourant->carteValide(getMain(), plis);
    vector<int> jouables(cartesJouables.begin(), cartesJouables.end());
    afficherCartesJouables(jouables, getMain());

    int indexCarteMain = choisirCarte(jouables);

    string valeur = getMain().getListeCartePaquet()[indexCarteMain]->getValeur();
    string couleur = getMain().getListeCartePaquet()[indexCarteMain]->getCouleur();

    getMain().giveCard(indexCarteMain, plis);

    cout << "\n>> " << getNom() << " joue : " << valeur << " de " << couleur << endl;

    attendreEntree("(Appuyez sur Entrée pour passer au joueur suivant...)");
}