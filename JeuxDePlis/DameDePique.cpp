#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include <limits>
#include "Team.h"
#include "DameDePique.h"
#include "TableJeu.h"
#include "Humain.h"
#include "IA.h"

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
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
}

DameDePique::DameDePique() {
    Jeu::setJeuCourant(this);
    nbJoueurs = 4;
    nbManche = 0;
    pointsGagnant = 25;
    ordreCarte = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Valet", "Dame", "Roi", "As" };
    table = new TableJeu();
    Coeur_Brise = false;
    premierPli = true;
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
        bool toutInterdit = true;
        for (const auto& carte : main.getListeCartePaquet())
            if (carte->getCouleur() != "Coeur" && !(premierPli && carte->getCouleur() == "Pique" && carte->getValeur() == "Dame"))
            {
                toutInterdit = false; break;
            }

        for (int i = 0; i < (int)main.PaquetSize(); i++) {
            const auto& carte = main.getListeCartePaquet()[i];
            bool estDamePique = premierPli && carte->getCouleur() == "Pique" && carte->getValeur() == "Dame";
            bool estCoeurInterdit = !checkCoeurBrise() && carte->getCouleur() == "Coeur";

            if (toutInterdit || (!estDamePique && !estCoeurInterdit))
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
                    cout << getJoueurById(i)->getNom() << " commence car 2 de Trèfle." << endl;
                    return i;
                }
            }
        }
    }
    return table->getIdPremierJoueur();
}

void DameDePique::compterPoint() {
    for (int i = 0; i < (int)getNbEquipe(); i++)
        getTeam()[i]->setPointManche(0);

    for (int i = 0; i < getNbJoueurs(); i++) {
        Team* team = getTeam()[i];
        for (const auto& pli : team->getPlisGagne())
            for (const auto& carte : pli.getListeCartePaquet()) {
                if (carte->getCouleur() == "Coeur")
                    team->setPointManche(team->getPointManche() + 1);
                else if (carte->getCouleur() == "Pique" && carte->getValeur() == "Dame")
                    team->setPointManche(team->getPointManche() + 13);
            }

        if (team->getPointManche() == 26) {
            cout << team->getTeamNom() << " a fait le grand chelem ! (+26 pour tous les autres)" << endl;
            team->setPointManche(0);
            for (int j = 0; j < (int)getNbEquipe(); j++)
                if (j != i) getTeam()[j]->setNbPoint(getTeam()[j]->getNbPoint() + 26);
        }
    }
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

void DameDePique::afficherScores() {
    cout << "=== SCORES ===" << endl;
    for (int i = 0; i < (int)getNbEquipe(); i++)
        cout << "  " << getTeam()[i]->getTeamNom() << " : " << getTeam()[i]->getPointManche() << " pts" << endl;
    cout << endl;
}

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
        echangerCartes(numeroManche);
        playFirst();
        premierPli = true;
        attendreEntree("(Appuyez sur Entree pour commencer la manche...)");

        int numPli = 1;
        while (getJoueurById(0)->getMain().PaquetSize() > 0) {
            int premierJoueur = table->getIdPremierJoueur();

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
                    joueur->jouerCoup();
                }
            }

            premierPli = false;

            if (!Coeur_Brise) {
                for (const auto& carte : table->getPlis().getListeCartePaquet())
                    if (carte->getCouleur() == "Coeur") { Coeur_Brise = true; break; }
            }

            int idgagnant = gagnantPlis();

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

            for (int i = 0; i < (int)getNbEquipe(); i++) {
                if (getTeam()[i]->getJoueurs()[0]->getIdjoueur() == idgagnant) {
                    getTeam()[i]->addPlisGagne(table->getPlis());
                    break;
                }
            }

            compterPoint();
            afficherScores();
            numPli++;

            attendreEntree("(Appuyez sur Entree pour continuer...)");
            clearConsole();
        }

        compterPoint();
        cout << "\n--- Resultat de la manche ---" << endl;
        for (int i = 0; i < (int)getNbEquipe(); i++) {
            getTeam()[i]->setNbPoint(getTeam()[i]->getNbPoint() + getTeam()[i]->getPointManche());
            cout << getTeam()[i]->getTeamNom() << " : +" << getTeam()[i]->getPointManche() << " pts" << endl;
        }
        cout << "\n--- Scores totaux ---" << endl;
        for (int i = 0; i < (int)getNbEquipe(); i++)
            cout << getTeam()[i]->getTeamNom() << " : " << getTeam()[i]->getNbPoint() << " pts" << endl;

        for (int i = 0; i < (int)getNbEquipe(); i++) {
            getTeam()[i]->clearPlis();
            getTeam()[i]->setPointManche(0);
        }
        creerPaquetJeu();
        numeroManche++;
        Coeur_Brise = false;
        premierPli = true;

        attendreEntree("\n(Appuyez sur Entree pour la prochaine manche...)");
    }
}

void DameDePique::echangerCartes(int numeroManche) {
    attendreEntree("On passe à l'échange des cartes appuyez sur Entree...");

    int type = (numeroManche - 1) % 4;

    vector<PaquetCarte> cartesADonner(getNbJoueurs());

    for (int i = 0; i < getNbJoueurs(); i++) {
        clearConsole();

        if (type == 3) {
            cout << "Pas de don à cette manche !" << endl;
            attendreEntree("(Appuyez sur Entree pour continuer...)");
            return;
        }

        string direction;
        if (type == 0) direction = "gauche";
        else if (type == 1) direction = "face";
        else direction = "droite";

        Joueur* joueur = getJoueurById(i);
        bool estIA = (dynamic_cast<Humain*>(joueur) == nullptr);

        for (int k = 0; k < 3; k++) {
            int indexCarte;
            if (estIA) {
                IA* ia = dynamic_cast<IA*>(joueur);
                indexCarte = ia->randomIndex((int)joueur->getMain().PaquetSize());
            }
            else {
                cout << "Donne 3 cartes au joueur de " << direction << " !" << endl;
                cout << "\n" << joueur->getNom() << " choisit 3 cartes a donner :" << endl;
                cout << "Votre main :" << endl;
                for (int j = 0; j < (int)joueur->getMain().PaquetSize(); j++) {
                    const auto& c = joueur->getMain().getListeCartePaquet()[j];
                    cout << "  " << j << " -> " << c->getValeur() << " de " << c->getCouleur() << endl;
                }
                cout << "Choisissez la carte " << k + 1 << "/3 (index) : ";
                cin >> indexCarte;
                while (indexCarte < 0 || indexCarte >= (int)joueur->getMain().PaquetSize()) {
                    cout << "Index invalide, reessayez : ";
                    cin >> indexCarte;
                }
            }
            const auto& c = joueur->getMain().getListeCartePaquet()[indexCarte];
            if (!estIA) {
                cout << "  Vous avez choisis : " << c->getValeur() << " de " << c->getCouleur() << endl;
            }
            joueur->getMain().giveCard(indexCarte, cartesADonner[i]);
        }

        if (!estIA)
        {
            attendreEntree("\n(Appuyez sur Entree pour terminer votre echange...)");
            clearConsole();

            attendreEntree("Passez au joueur suivant appuyez sur Entree...");
            clearConsole();
        }
    }

    for (int i = 0; i < getNbJoueurs(); i++) {
        int destination;
        if (type == 0)      destination = (i + 1) % getNbJoueurs();
        else if (type == 1) destination = (i + 2) % getNbJoueurs();
        else                destination = (i - 1 + getNbJoueurs()) % getNbJoueurs();

        while (cartesADonner[i].PaquetSize() > 0)
            cartesADonner[i].giveCard(0, getJoueurById(destination)->getMain());
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
			int pointsEquipeGagnant = getTeam()[0]->getNbPoint();
			string nomEquipeGagnant =  getTeam()[0]->getTeamNom();
            for (size_t j = 0; j < getNbEquipe(); j++) {
                if (getTeam()[j]->getNbPoint() > pointsEquipeGagnant) {
                    pointsEquipeGagnant = getTeam()[j]->getNbPoint();
                    nomEquipeGagnant = getTeam()[j]->getTeamNom();
                }
            }
            return true;

        }
    }
    return false;
}