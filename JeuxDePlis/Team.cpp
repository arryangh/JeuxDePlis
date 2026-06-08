// Team.cpp
#include "Team.h"

// constructeur par défaut de Team, instancie les attributs à 0
Team::Team() : pointManche(0), nbPoint(0), teamNom('\0') {}

// constructeur de confort avec le nom de l'équipe
Team::Team(string nomTeam) : pointManche(0), nbPoint(0), teamNom(nomTeam) {}

void Team::clearPlis() {
    this->plisGagne.clear();
}

/*
la fonction prend un unique_ptr en paramètre.l'objet appelant de la fonction transfert la propriété de du pointeur 
de vector à la fonction. on utilise  move car unique_ptr ne peut pas être recopié, mais seulement déplacé.
à la fin de l'appel, le unique_ptr de l'appelant reste à null (vector<unique_ptr<PaquetCarte>> plisGagne)
*/
void Team::setPlisGagne(unique_ptr<PaquetCarte> plis) {
    this->plisGagne.push_back(move(plis));
}


/*
La fonction retourne un pointeur brut sans transferer sa propriété pour consulter le vector "plisGagne"
*/
PaquetCarte* Team::getPlisGagne() {
    if (this->plisGagne.empty()) return nullptr;
    return this->plisGagne.back().get();
}


void Team::setPointManche(int nb) {
    this->pointManche = nb;
}

int Team::getPointManche() {
    return this->pointManche;
}

void Team::setNbPoint(int nb) {
    this->nbPoint = nb;
}

int Team::getNbPoint() {
    return this->nbPoint;
}

void Team::setTeamNom(char nom) {
    this->teamNom = nom;
}

char Team::getTeamNom() {
    return this->teamNom;
}

/*
on recoit le vecteur par valeur et on le move dans l'attribut "joueurs"
joueur est un shared_ptr qui devient propriétaire du vecteur sans devoir faire une copie inutile (il pointe vers 
le vector existant)
*/
void Team::setJoueurs(vector<shared_ptr<Joueur>> joueurs) {
    this->joueurs = move(joueurs);
}

// la méthode appelant renvoie "le vecteur pointeur partagé de joueur" par valeur
vector<shared_ptr<Joueur>> Team::getJoueurs() {
    return this->joueurs;
}