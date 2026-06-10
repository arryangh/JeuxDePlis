#include "JeuManager.h"
#include "DameDePique.h"

void JeuManager::afficherText(string s) {
    cout << s << endl;
}

int JeuManager::ChoixDuJeu() {
    bool inBoucle = true;
    int choix;


    while (inBoucle) {
        afficherText("Bien Venu dans JeuDePlis!");
        afficherText("Choisissez votre jeu de Plis");
        afficherText("1: Dame De Pique");
        afficherText("2: Jeu 2");
        afficherText("3: Jeu 3");

        cout << "Votre choix: ";
        cin >> choix;

        switch (choix) {
        case 1:
            afficherText("vous avez choisi le jeu \"1\"");
            break;
        case 2:
            afficherText("vous avez choisi le jeu \"2\"");
            break;
        case 3:
            afficherText("vous avez choisi le jeu \"3\"");
            break;
        default:
            afficherText("Choix invalide! Veuillez entrer 1, 2 ou 3.");
            break;
        }

        afficherText("Appuyez sur 0 pour quitter ou 1 pour continuer");
        cin >> choix;
        if (choix == 0) {
            inBoucle = false;
        }
    }
    return choix; // forcement une valeur entier 1, 2, 3, ...
}


Jeu* JeuManager::InstancierJeuChoisi(int choix) {
    switch (choix) {
    case 1:
        return new DameDePique();

    case 2:
        return nullptr; // Belote

    case 3:
        return nullptr;// coinche

    default:
        return nullptr;
    }
}