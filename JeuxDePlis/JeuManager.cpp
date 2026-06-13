#include "JeuManager.h"
#include "DameDePique.h"
#include "Humain.h"
#include "IA.h"
#include "Team.h"

void JeuManager::afficherText(string s) {
    cout << s << endl;
}

int JeuManager::ChoixDuJeu() {
    int choixJeu = 0;
    bool confirme = false;

    while (!confirme) {
        while (choixJeu < 1 || choixJeu > 3) {
            afficherText("Bienvenue dans JeuDePlis !");
            afficherText("Choisissez votre jeu :");
            afficherText("1: Dame De Pique");
            afficherText("2: Jeu 2");
            afficherText("3: Jeu 3");
            cout << "Votre choix: ";
            cin >> choixJeu;
            if (choixJeu < 1 || choixJeu > 3)
                afficherText("Choix invalide ! Veuillez entrer 1, 2 ou 3.");
        }

        afficherText("Etes-vous sur de votre choix ? (0: oui, 1: changer)");
        int confirm;
        cin >> confirm;
        if (confirm == 0)
            confirme = true;
        else
            choixJeu = 0;
    }

    return choixJeu;
}

Jeu* JeuManager::InstancierJeuChoisi(int choix) {
    switch (choix) {
    case 1:
        return new DameDePique();
    case 2:
        return nullptr; // Belote
    case 3:
        return nullptr; // Coinche
    default:
        return nullptr;
    }
}

void JeuManager::ConfigurerJeu(int nbJoueurs, int nbManches) {
    Jeu* jeuCourant = Jeu::getJeuCourant();
    jeuCourant->setNbJoueurs(nbJoueurs);
    jeuCourant->setNbManche(nbManches);
}

void JeuManager::ConfigurerJoueurs() {
    Jeu* jeuCourant = Jeu::getJeuCourant();
    int nbJoueurs = jeuCourant->getNbJoueurs();

    for (int i = 0; i < nbJoueurs; i++) {
        int choix = -1;
        while (choix != 0 && choix != 1) {
            afficherText("Joueur " + to_string(i + 1) + " : IA ou Humain ? (0 = IA, 1 = Humain)");
            cin >> choix;
            if (choix != 0 && choix != 1)
                afficherText("Choix invalide! Entrez 0 ou 1.");
        }

        string nom;
        afficherText("Nom du joueur " + to_string(i + 1) + " : ");
        cin >> nom;

        shared_ptr<Joueur> joueur;
        if (choix == 0) {
            IA* ia = new IA();
            ia->setIdJoueur(i);
            ia->setNom(nom);
            joueur = shared_ptr<Joueur>(ia);
        }
        else {
            Humain* humain = new Humain();
            humain->setIdJoueur(i);
            humain->setNom(nom);
            joueur = shared_ptr<Joueur>(humain);
        }
        jeuCourant->addJoueur(joueur);
    }
}