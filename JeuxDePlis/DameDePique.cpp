#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include "Team.h"
#include "DameDePique.h"
#include "TableJeu.h"
#include "Humain.h"

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

DameDePique::DameDePique() {
    Jeu::setJeuCourant(this);
    nbJoueurs = 4;
    nbManche = 0;
    pointsGagnant = 25;
    ordreCarte = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Valet", "Dame", "Roi", "As" };
    table = new TableJeu();
    Coeur_Brise = false;
}

const int DameDePique::playNext() {
    return gagnantPlis();
}

void DameDePique::distribuer() {
    int i = 0;
    while (getPaquetJeu().PaquetSize() > 0) {
        getPaquetJeu().giveCard(0, getJoueurById(i)->getMain());
        i = (i + 1) % getNbJoueurs();
    }
    cout << "=== Cartes distribuees - bonne chance ! ===" << endl;
}

list<int> DameDePique::carteValide(const PaquetCarte& main, const PaquetCarte& plis) {
    list<int> carteValide;
    if (plis.PaquetSize() == 0) {
        if (checkCoeurBrise()) {
            for (int i = 0; i < (int)main.PaquetSize(); i++)
                carteValide.push_back(i);
        }
        else {
            // Verifie si le joueur n'a QUE des coeurs
            bool toutCoeur = true;
            for (const auto& carte : main.getListeCartePaquet())
                if (carte->getCouleur() != "Coeur") { toutCoeur = false; break; }

            for (int i = 0; i < (int)main.PaquetSize(); i++)
                if (toutCoeur || main.getListeCartePaquet()[i]->getCouleur() != "Coeur")
                    carteValide.push_back(i);
        }
    }
    else {
        Carte firstCartePlis = *plis.getListeCartePaquet()[0];
        if (firstCartePlis.checkCouleurPlisDansMain(main)) {
            string firstCouleur = plis.getListeCartePaquet()[0]->getCouleur();
            for (int i = 0; i < (int)main.PaquetSize(); i++)
                if (main.getListeCartePaquet()[i]->getCouleur() == firstCouleur)
                    carteValide.push_back(i);
        }
        else {
            for (int i = 0; i < (int)main.PaquetSize(); i++)
                carteValide.push_back(i);
        }
    }
    return carteValide;
}

const int DameDePique::playFirst() {
    TableJeu* table = &getTable();
    if (getJoueurById(0)->getMain().PaquetSize() == 13) {
        for (int i = 0; i < getNbJoueurs(); i++) {
            for (const auto& carte : getJoueurById(i)->getMain().getListeCartePaquet()) {
                if (carte->getValeur() == "2" && carte->getCouleur() == "Trèfle") {
                    table->setIdPremierJoueur(i);
                    cout << getJoueurById(i)->getNom() << " commence (possède le 2 de Trèfle)." << endl;
                    return i;
                }
            }
        }
    }
    return table->getIdPremierJoueur();
}

void DameDePique::compterPoint() {
    cout << "\n--- Resultat de la manche ---" << endl;
    for (int i = 0; i < getNbJoueurs(); i++) {
        int pointManche = 0;
        for (const auto& pli : getTeam()[i]->getPlisGagne())
            for (const auto& carte : pli.getListeCartePaquet()) {
                if (carte->getCouleur() == "Coeur") pointManche += 1;
                else if (carte->getCouleur() == "Pique" && carte->getValeur() == "Dame") pointManche += 13;
            }

        if (pointManche == 26) {
            cout << getTeam()[i]->getTeamNom() << " a fait le grand chelem ! (+26 pour tous les autres)" << endl;
            pointManche = 0;
            for (int j = 0; j < (int)getNbEquipe(); j++)
                if (j != i) getTeam()[j]->setNbPoint(getTeam()[j]->getNbPoint() + 26);
        }
        getTeam()[i]->setNbPoint(getTeam()[i]->getNbPoint() + pointManche);
        cout << getTeam()[i]->getTeamNom() << " : +" << pointManche << " pts cette manche" << endl;
    }

    cout << "\n--- Scores cumules ---" << endl;
    for (int i = 0; i < (int)getNbEquipe(); i++)
        cout << getTeam()[i]->getTeamNom() << " : " << getTeam()[i]->getNbPoint() << " pts" << endl;
}

void DameDePique::configurerTeam() {
    vector<Team*> teams;
    for (auto& joueur : joueurs) {
        Team* team = new Team(joueur->getNom());
        team->setJoueurs({ joueur });
        teams.push_back(team);
    }
    setTeam(teams);
}

// Affiche les scores de tous les joueurs
void DameDePique::afficherScores() {
    cout << "=== SCORES ===" << endl;
    for (int i = 0; i < (int)getNbEquipe(); i++)
        cout << "  " << getTeam()[i]->getTeamNom() << " : " << getTeam()[i]->getNbPoint() << " pts" << endl;
    cout << endl;
}

// Affiche les cartes posees sur la table avec le nom du joueur qui les a jouees
void DameDePique::afficherPliEnCours(int premierJoueur) {
    PaquetCarte& plis = getTable().getPlis();
    if (plis.PaquetSize() == 0) {
        cout << "Pli : vous commencez !" << endl;
    }
    else {
        cout << "Pli en cours : ";
        for (size_t k = 0; k < plis.PaquetSize(); k++) {
            const auto& c = plis.getListeCartePaquet()[k];
            string nom = getJoueurById((premierJoueur + (int)k) % getNbJoueurs())->getNom();
            cout << nom << " [" << c->getValeur() << " de " << c->getCouleur() << "]  ";
        }
        cout << endl;
    }
}

void DameDePique::jouer() {
    TableJeu* table = &getTable();
    creerPaquetJeu();
    int numeroManche = 1;

    while (!checkWin()) {
        clearConsole();
        cout << "========== MANCHE " << numeroManche << " ==========" << endl;
        paquetJeu.MelangerPaquet();
        distribuer();
        playFirst();
        attendreEntree("(Appuyez sur Entree pour commencer la manche...)");

        int numPli = 1;
        while (getJoueurById(0)->getMain().PaquetSize() > 0) {
            int premierJoueur = table->getIdPremierJoueur();

            // Chaque joueur joue a son tour
            for (int i = 0; i < getNbJoueurs(); i++) {
                int idJoueur = (premierJoueur + i) % getNbJoueurs();
                Joueur* joueur = getJoueurById(idJoueur);

                bool estIA = (dynamic_cast<Humain*>(joueur) == nullptr);
                if (estIA) {
                    clearConsole();
                    cout << "=== Tour de : " << joueur->getNom() << " (IA) ===" << endl << endl;
                    afficherScores();
                    afficherPliEnCours(premierJoueur);
                    cout << endl;

                    // L'IA joue, on affiche ce qu'elle a joue
                    size_t tailleAvant = table->getPlis().PaquetSize();
                    joueur->jouerCoup();
                    if (table->getPlis().PaquetSize() > tailleAvant) {
                        const auto& c = table->getPlis().getListeCartePaquet().back();
                        cout << ">> " << joueur->getNom() << " joue : "
                            << c->getValeur() << " de " << c->getCouleur() << endl;
                    }
                    attendreEntree("(Appuyez sur Entree pour continuer...)");
                }
                else {
                    // jouerCoup() de Humain gere son propre affichage et clear
                    joueur->jouerCoup();
                }
            }

            // Verifie si les coeurs sont brises
            if (!Coeur_Brise) {
                for (const auto& carte : table->getPlis().getListeCartePaquet())
                    if (carte->getCouleur() == "Coeur") { Coeur_Brise = true; break; }
            }

            int idgagnant = gagnantPlis();

            // Resultat du pli
            clearConsole();
            cout << "--- Resultat du pli " << numPli << " ---" << endl << endl;
            for (size_t k = 0; k < table->getPlis().PaquetSize(); k++) {
                const auto& c = table->getPlis().getListeCartePaquet()[k];
                string nom = getJoueurById((premierJoueur + (int)k) % getNbJoueurs())->getNom();
                cout << "  " << nom << " : " << c->getValeur() << " de " << c->getCouleur() << endl;
            }
            cout << "\n--> " << getJoueurById(idgagnant)->getNom() << " remporte le pli !" << endl;
            if (Coeur_Brise) cout << "  (Les coeurs sont brises)" << endl;

            cout << endl;
            afficherScores();

            // Donner le pli a l'equipe gagnante
            for (int i = 0; i < (int)getNbEquipe(); i++)
                for (const auto& j : getTeam()[i]->getJoueurs())
                    if (j->getIdjoueur() == idgagnant) {
                        getTeam()[i]->addPlisGagne(table->getPlis());
                        goto plisAttribue;
                    }
        plisAttribue:
            numPli++;

            attendreEntree("(Appuyez sur Entree pour continuer...)");
            clearConsole();
        }

        compterPoint();
        for (int i = 0; i < (int)getNbEquipe(); i++)
            getTeam()[i]->clearPlis();
        creerPaquetJeu();
        numeroManche++;
        Coeur_Brise = false;

        attendreEntree("\n(Appuyez sur Entree pour la prochaine manche...)");
    }
}

Jeu* DameDePique::getInstance() {
    return getJeuCourant();
}

void DameDePique::creerPaquetJeu() {
    for (const string& couleur : Couleur)
        for (const string& valeur : ordreCarte) {
            unique_ptr<Carte> carte = make_unique<Carte>();
            carte->setCouleur(couleur);
            carte->setValeur(valeur);
            getPaquetJeu().addCarte(move(carte));
        }
}

int DameDePique::gagnantPlis() {
    TableJeu& table = getTable();
    PaquetCarte& plis = table.getPlis();
    int idFirstJoueur = table.getIdPremierJoueur();
    string firstCouleur = plis.getListeCartePaquet()[0]->getCouleur();

    int indexGagnant = 0;
    int idgagnant = idFirstJoueur;

    for (int i = 1; i < getNbJoueurs(); i++) {
        const auto& carte = plis.getListeCartePaquet()[i];
        if (carte->getCouleur() == firstCouleur && CompareCarte(carte, plis.getListeCartePaquet()[indexGagnant])) {
            indexGagnant = i;
            idgagnant = (idFirstJoueur + i) % getNbJoueurs();
        }
    }
    table.setIdPremierJoueur(idgagnant);
    return idgagnant;
}

bool DameDePique::checkCoeurBrise() {
    return Coeur_Brise;
}

bool DameDePique::checkWin() {
    for (size_t i = 0; i < getNbEquipe(); i++) {
        if (getTeam()[i]->getNbPoint() >= getPointsGagnant()) {
            cout << "\n*** " << getTeam()[i]->getTeamNom()
                << " a atteint " << getPointsGagnant() << " points - partie terminee ! ***" << endl;
            return true;
        }
    }
    return false;
}